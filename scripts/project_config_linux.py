import subprocess
import os 

def distro_name():
    try:
        with open("/etc/os-release", "r") as f:
            for line in f:
                if line.startswith("NAME="):
                    return line.strip().split("=")[1].strip('"')
    except FileNotFoundError:
        return "Unknown distribution"

def install_depedencies_on_arch(dep_name):
    subprocess.run(["pacman", "-S", dep_name])

def install_depedencies_on_ubuntu(dep_name):
    subprocess.run(["apt", "install", dep_name])

def install_depedencies_on_fedora(dep_name):
    subprocess.run(["dnf", "install", dep_name])

current_distro_name = distro_name()

if current_distro_name == "Arch Linux":
    install_depedencies_on_arch("nmap")
    install_depedencies_on_arch("boost")
    install_depedencies_on_arch("cmake")
    install_depedencies_on_arch("ninja")
elif current_distro_name == "Ubuntu":
    install_depedencies_on_ubuntu("nmap")
    install_depedencies_on_ubuntu("boost")
    install_depedencies_on_ubuntu("cmake")
    install_depedencies_on_ubuntu("ninja-build")
elif current_distro_name == "Fedora Linux":
    install_depedencies_on_fedora("nmap")
    install_depedencies_on_fedora("boost")
    install_depedencies_on_fedora("cmake")
    install_depedencies_on_fedora("ninja")

os.makedirs("build", exist_ok=True)
os.chdir("build")
subprocess.run(["cmake","-G","Ninja",".."])
subprocess.run(["ninja"])