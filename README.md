# Qpdf Tools

Qpdf Tools is an easy-to-use Qt interface for [Ghostscript](https://www.ghostscript.com/) and [Stapler](https://github.com/hellerbarde/stapler), which makes it possible for normal users to manage their PDFs.

With Qpdf Tools, you can easily compress, split, merge and even rotate your pdf documents.

## How to install?

If you just want to use the program to manage your PDFs, We have .deb packages available for download in https://github.com/silash35/qpdftools/releases. If you installed Qpdf tools by a .deb package of version equal to or above 1.2 you will receive updates automatically from our APT repository

Perhaps, in the future, snaps packages and a Windows software version (.exe) may be produced.

Build packages and maintain them is a hard thing, so we have a [repository](https://github.com/silash35/qpdftools-packages) only for that task. Please, help us to keep Qpdf Tools available for users, whatever their operating system.

## How to contribute?

First, I recommend installing the .deb package even if you intend to run the program from the source code. So that all the necessary facilities will be installed automatically. Also, the translations and icons will be placed in the correct folders.

Then make the repository git clone

	git clone https://github.com/silash35/qpdftools.git

Finally, open the project with Qt Creator and compile. If no errors occur you can make the changes you want and then share the improvements with us.
We currently need more help to:

 - Make Qpdf Tools packages for other package managers, as in Snap, for Pacman (Arch Linux) and others.
 - Keep the deb package up and running.
 - Test whether Qpdf Tools works correctly on other Linux distributions
 - Translating the program into other languages
