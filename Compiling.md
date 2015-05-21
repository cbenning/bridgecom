# Dependencies #

## Randoms ##
  * Install dependencies:
    * `sudo apt-get -y install build-essential xserver-xorg-dev x11proto-xf86vidmode-dev libxxf86vm-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libxext-dev libxcursor-dev libpng-dev libjpeg-dev`

## Irrlicht ##

Need to install irrlicht. This howto worked well for me on debian wheezy (testing)

http://irrlicht3d.org/wiki/index.php?n=Main.InstallingIrrlicht

Here is a summary:

  * Get latest version of Irrlicht(download/svn)

  * In the Irrlicht folder type:
    * `cd source/Irrlicht && make`
  * Install the library and headers from the directory irrlicht-1.#
    * Type: `cd ../..`
    * Type: `sudo cp -r include/* /usr/local/include/`
    * Type: `sudo cp lib/Linux/libIrrlicht.a /usr/local/lib`

# The Game #

  * Checkout the code
    * [UsingGit](UsingGit.md)
  * Compile
    * make
  * Run
    * ./run.sh