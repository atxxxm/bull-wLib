#!/bin/bash
if [ -f /etc/os-release ]; then
    source /etc/os-release
    DISTRO="$ID"
else
    echo "Не удалось определить дистрибутив!"
    exit 1
fi

case "$DISTRO" in
    "ubuntu" | "debian")
        echo "Установка пакетов для Debian/Ubuntu..."
        sudo apt install libarchive-dev -y
        ;;
    "centos" | "fedora" | "rhel")
        echo "Установка пакетов для CentOS/Fedora/RHEL..."
        sudo dnf install libarchive-devel 
        ;;
    "arch")
        echo "Установка пакетов для Arch Linux..."
        sudo pacman -Sy libarchive
        ;;
    "opensuse-leap" | "opensuse-tumbleweed")
        echo "Установка пакетов для openSUSE..."
        sudo zypper install libarchive-devel
        ;;
    *)
        echo "Дистрибутив не поддерживается: $DISTRO"
        exit 1
        ;;
esac

echo "Установка библиотеки libarchive завершена!"

g++ src/main.cpp src/bull.cpp src/slog.cpp src/archive.cpp -o bull -larchive
sudo chmod +x ./bull
sudo mv bull /usr/local/bin/


