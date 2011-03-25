-----------------
  Translate AS1
-----------------

The Translate framework is a compiler for Macromedia's ActionScript language, 
Version 1.x. Scripts are compiled to generate the binary encoded byte-codes 
and actions that are executed by the Flash Player.

-------------
  Licensing
-------------
Translate AS1 is made available under the terms of the Berkeley Software 
Distribution (BSD) license. This allow you complete freedom to use and distribute
 the code in source and/or binary form as long as you respect the original 
 copyright. Please see the LICENSE.txt file for exact terms.

---------------------
  Project Structure
---------------------
Translate AS1 is distributed with the following top-level directory structure:

  --+-- build
    |    
    +-- config
    |
    +-- docs
    |
    +-- examples
    |
    +-- source


1. build contains a set of project files which can be used to build the framework with 
different development tools. The current set of development tools supported is:

    Ant, Version 1.6 or higher

    CMake, Version 2.0 or higher

    Visual Studio.NET 2002

    Visual Studio.NET 2003

See below for information on compiling the framework with the different tools.


2. config contain configuration files used to generate the documentation for the 
framework. It contains the following sub-directories:

 config --+-- doxygen
          |
          +-- images

(a) doxygen contains the files used to generate the datasheets for each class using 
Doxygen.

(b) images contains the images for the datasheet header and all the figures used in
describing how Flash and the Transform SWF classes work.


3. docs contains documentation for the project. It contains the following sub-directories:

 docs --+-- datasheets
        |
        +-- issues
        |
        +-- releases

(a) datasheets contains descriptions of each class generated using doxygen. A target is 
included in the ANT project file to (re)generate the datasheets from the source header files
using doxygen. The pages generated are placed in this directory.

(b) issues is a list (currently in HTML) of all the known issues with the current release.
A more up to date list may be found on the Flagstone web site.

(c) releases is a set (currently in HTML) of the most recent release notes for the framework.
A complete set can be found on the Flagstone web site.


4. examples contains a set of files which illustrate how to use the different classes in 
Translate AS1 to generate Flash files.


5. source contains the grammar files and source code for all the classes that make up the 
Translate AS1 framework.

----------------
  Requirements
----------------
Translate AS1 was built using the rather excellent ANTLR. You can either get the source from
www.antlr.org or you get download and install the libraries used to compile this release from 
the Flagstone web site, www.flagstonesoftware.com/downloads/index/html. ANTLR makes heavy use
of the C++ standard library so be sure to download the correct version for the compiler you 
are using as the libraries are not binary compatible.

There are two parts to building Translate AS1:

    1) Compile the grammar files to generate the C++ classes for the parser.
    2) Compile all the classes to build the library.

The release contains all the generated classes from Step 1 so you can avoid this unless you 
want to tweak the grammar files.

The project build files assume the antlr library and header files can be found in the following 
locations:

    Windows: 

        C:\Program Files\Flagstone\lib
        C:\Program Files\Flagstone\include\antlr

    Unix, Linux, Mac OS X:

        /usr/local/lib
        /usr/local/include/antlr

The JAR file containing the Java classes used to perform the code generation should be installed
in the following locations:

    Windows: 

        C:\Program Files\Flagstone\java

    Unix, Linux, Mac OS X:

        /usr/local/java


Only the location of the header files are required to compile the Transform library. The 
location of the antlr library is only required when peforming the final link stage for an
application that uses the Translate AS1 library.

If the library and header files are installed in another location you will have to edit the 
respective project build file to update the location:

Ant: The properties files, windows.properties and unix.properties each contain three property 
definitions that specify the name of the library, the directory it is in and the directory
where the header files are located. When running Ant only the properties file specific to your
platform will be loaded so you do not need to edit both files.

CMake: The file CMakeLists.txt contains variables that define the location of antlr. Edit 
accordingly.

Visual Studio.NET: You will need to edit the property pages for the transform project to 
change the following setting:

    C/C++ -> Additional Include Directories


-----------------------
  Compiling Using Ant
-----------------------
To use Ant to compile Translate AS1 you will need:

    Ant 1.6 or higher.             (ant.apache.org)
    Ant-contrib 1.0 or higher.     (ant-contrib.sourceforge.net)
    Cpptasks 1.0 or higher.        (ant-contrib.sourceforge.net)

Install Ant then copy the ant-contrib and cpptasks jars into the lib directory of the 
Ant installation. Your path and environment variables should be set to allow the compiler 
and linker to run from the command line*.

The ant build file (and the files it imports) contains the following targets:

    clean        remove all files (and datasheets) generated.
    library      compile the classes and build the library.
    datasheets   generate the datasheets using Doxygen from comments in the header files.
    install      install the library and the header files.
    uninstall    remove the installed library and header files.
    examples     compile the code in the examples directory.

    grammar      generate the C++ classes from the grammar files.


The 'library' target defines properties controlling the name of the compiler and whether 
the files should be compiled with debugging information. You can override the defaults by 
setting their values from the command line:

    ant -Dcompiler=vc70 -Ddebug=true library

The current list of compilers supported are:

    vc70  Visual C++ 7.0
    vc71  Visual C++ 7.1

* For Visual Studio.NET, the file Common7\Tools\vsvars32.bat in your installation contains
the definitions. You can run this batch file from the command line prior to running Ant 
or set the environment variables via System Properties in the Control Panel.


-------------------------
  Compiling Using CMake
-------------------------
CMake is a cross-platform tool which can be used to build makefiles (Borland, NMake or Unix)
or Visual Studio project files to compile a project. The latest release can be found at
http://www.cmake.org

Run the CMakeSetup application:

    1. Select the directory where the CMakeLists.txt file is located as the location of the 
       source code - the files are specified relative to this file.

    2. Select the directory where the project files will be generated - a subdirectory below
       the one containing the CMakeLists.txt file is a good choice.

    3. Select the type of project file you want to generate.

    4. Click the configure button to identify the installed compiler and other environment 
       variables.

    5. Click the ok button to generate the project files.


    6. Build the library and examples using the generated project files.


NOTES: 

1. Currently the only way to generate the classes from the grammar files is to use Ant.

2. CMake currently does not install the files when used under Windows.

3. When using CMake in windows to generate Visual C++ files be sure to select the correct
runtime library. In CMake the default is either Multi-threaded DLL, /Md or Multi-threaded Debug 
DLL, /Mdd. The correct runtime library is Multi-threaded, /Mt.

------------------------------------
 Compiling Using Visual Studio.NET
------------------------------------
Project files are included for Visual Studio.NET 2002 and 2003 since the project file format 
is not compatible.

Build the translate target from the project. Debug and Release configurations are available.

Note the only way to generate the classes from the grammar files is to use Ant.

--------------------------
  Additional Information
--------------------------

For Further Information please contact:

Stuart MacKay
Flagstone Software Ltd.
92 High Street
Wick, Caithness KW1 4LY
Scotland

www.flagstonesoftware.com
