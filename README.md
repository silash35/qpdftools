# Qpdf Tools

Qpdf Tools is an easy-to-use Qt interface for [Ghostscript](https://www.ghostscript.com/) and [Stapler](https://github.com/hellerbarde/stapler), which makes it possible for normal users to manage their PDFs.

With Qpdf Tools, you can easily compress, split, merge and even rotate your pdf documents.

## How to install?

If you just want to use the program to manage your PDFs, We have .deb packages available for download in https://github.com/silash35/qpdftools/releases. If you installed Qpdf tools by a .deb package of version equal to or above 1.2 you will receive updates automatically from our APT repository.

If your distribution is Arch Linux or similar (Like Manjaro) I recommend installing it through AUR. Just search for the "qpdftools" package

Perhaps, in the future, snaps packages and a Windows software version (.exe) may be produced.

Build packages and maintain them is a hard thing, so we have a [repository](https://github.com/silash35/qpdftools-packages) only for that task. Please, help us to keep Qpdf Tools available for users, whatever their operating system.

## How to install from source?

Installing from source is not recommended for normal users. Only do this if you already have experience with this process.
First of all, uninstall any other version of Qpdf Tools (including the .deb package), and install the necessary dependencies: ghostscript (>=9.25), stapler(>=1.0), breeze-icon-theme(>= 5.40), and also Qt5.
Then do the git clone of the project:

	git clone https://github.com/silash35/qpdftools.git

Check if you have installed the necessary dependencies in your distribution to compile a project in Qt. If you don't know, just install Qtcreator (In Debian-based distros, such as ubuntu and Linux Mint, it is also necessary to install the "qt5-default" package).

Finally, open the terminal in the project folder and run the following commands:

	mkdir build
	cd build
	cmake ..
	make

and then the process of compiling Qpdf Tools will start. To install, run the command below as root (sudo)

	make install

If you want to uninstall the program, you will need to remove each file manually. To do this, run the command below, again as root:

	rm /usr/bin/qpdftools /usr/share/pixmaps/qpdftools.svg /usr/lib/qpdftools/* /usr/share/applications/qpdftools.desktop && rmdir /usr/lib/qpdftools

## How to contribute?

First, I recommend installing the .deb package even if you intend to run the program from the source code. So that all the necessary facilities will be installed automatically. Also, the translations and icons will be placed in the correct folders. Qpdf Tools only recognizes icon files and translations if they are in the right folders. So if Qpdf Tools is not installed on the system it will not work correctly.

Then make the repository git clone

	git clone https://github.com/silash35/qpdftools.git

Finally, open the project with your favorite IDE, preferably compatible with Cmake, and compile. If no errors occur you can make the changes you want and then share the improvements with us.
We currently need more help to:

 - Make Qpdf Tools packages for Snap, Flatpak and etc
 - Keep the deb package up and running.
 - Keep the AUR PKGBUILD up and running.
 - Test whether Qpdf Tools works correctly on other Linux distributions
 - Translating the program into other languages
