Unpacker and Game Resource Packer PUP
=====================================

Background
-----------

In the early 2000s, I liked to wander in games and get various resources out of them - graphics, sounds, models. My main and only tools then were the hexadecimal editors pview and hiew, the Pascal compilers and C/C. I did quite a lot, however then I was interested only to get resources out of games, but not to make tools for editing.

Some file formats have been analyzed surface at a level sufficient to extract data, but no more. Some were analyzed pretty well, so I was even able to implement not only data extraction but back packing as well.

After a while, I was trapped in PLO debuts, so it began to take so long to design the object structure of the program that I could not complete any program. It was the beginning of a "creative depression" that left me dropping programming for a long time.

History
-------

In September 2010, I decided to shake the old man and write a program for unpacking and packing files with game resources. In order not to repeat past mistakes, I decided to write on pure C, without using the PLO. I designed a plugin system and decided to implement in this program support only those formats that fall well on it.

By February 2011, I had almost completed the development of the program, planning to add support for another format (IWAD/PWAD). Difficulties arose with this format and work stalled. Although I periodically recalled the program and tried to finish the support of this format, eventually I found some more interesting activity and forgot about this program.

Recently I remembered her and thought - not to disappear good, maybe who will use it. Tried to collect, corrected a couple of mistakes, because of which the assembly did not go, removed the beginnings of the failed plugin and decided to put all this out.

Since by 2010 I was already using Debian, the program was also done on it. Assembly is carried out by means of Shell script, for assembly packages gcc, zlib1g, zlib1g-dev are necessary. No assembly was tested on other systems.

Program
---------

The program is called PUP - Packer/UnPacker (the word pup can also be translated from English as "puppy"). The program has several modes of operation:

1. If the program is running without options, help on the available options is displayed.
2. If you specify the --list option, the program displays a description of all available plugins.
3. If you specify the --unpack option, the program attempts to determine the format of the specified file and decompresses its contents to the specified directory, and saves the metadata of the file to the specified file. If you do not specify a metadata file name, the directory name with the .txt extension added to it is used. If no directory name is specified, the file name without the extension is used. To prevent the program from trying to define the file format itself, you can specify the --plugin option with a specific format.
4. If you specify the --pack option, the program will pack the data into the specified file from the specified directory using the metadata from the specified file. If you do not specify a metadata file name, the directory name with the .txt extension added to it is used. If no directory name is specified, the file name without the extension is used. When packing, be sure to specify the --plugin option with the format of the generated file.
5. If you specify the --savemeta option, the program tries to determine the format of the specified file and save the metadata to the specified file. If the plugin does not contain metadata, the program will report it and exit. If you do not specify a metadata file name, the source file name with the extension replaced by .txt is used. To prevent the program from trying to define the file format itself, you can specify the --plugin option with a specific format.
6. If you specify the --print option, the program outputs to the standard output the technical information from the resource directory of the specified file (resource offset, its compressed and original size, resource name, etc.). To prevent the program from trying to determine the file format itself, you can specify the --plugin option with the specified format.

Program Help:

    $ ./pup
    Usage: pup --list
           pup --plugin <plugin> --pack <file> [<dir> [<meta>]]
           pup [--plugin <plugin>] --unpack <file> [<dir> [<meta>]]
           pup [--plugin <plugin>] --savemeta <file> [<meta>]
           pup [--plugin <plugin>] --print <file>
    Options:
           --plugin <plugin>   - specify certain plugin
    Modes:
           --list     - list of all supported plugins
           --pack <file> [<dir> [<meta>]]  - packing dir to specified file
           --unpack <file> [<dir> [<meta>]]  - unpacking specified file to dir
           --savemeta <file> [<meta>]  - only save metadata to specified metafile
           --print <file>    - print technical information to stdout

List of supported formats:

    $ ./pup --list
    Supported plugins:
    grp     GRP-files of Duke Nukem 3D, Witchaven, Redneck Rampage, Shadow Warrior
    gob     GOB-files of Star Wars: Dark Forces
    pak     PAK-files of Dune II: The Building of a Dynasty
    viv     VIV-files of the Need For the Speed 3: Hot Pursuit
    vpp     VPP-files of Red Faction, The Punisher, Summoner
    pack    PAK-files of Quake, Quake II, Half-Life, Heretic 2, MDK 2
    pack2   PAK-files of Daikatana
    wad2    WAD-file of Quake
    wad3    WAD-files of Half-Life
    res     RES-file of Comanche 3
    dpk4    DPK-file of Starmageddon 2
    dat     DAT-files of Fallout
    dat2    DAT-files of Fallout 2
    rff20   RFF-files of Blood, version 2.0
    rff30   RFF-files of Blood, version 3.0
    rff31   RFF-files of Blood, version 3.1

The program works perfectly with the definition of the source file type, so it is not necessary to specify the plugin used. The plugin needs to be specified only when packing so that the program generates a file of the format you want.

Metadata is used only in RFF format. Metadata is additional information fields that accompany each packaged file. These fields cannot be recovered from the contents of the file itself, so when you unpack the RFF file, you must save the fields to a text file and load them from a text file when packing.

There are many different packers and game file unpackers. The uniqueness of my program lies in supporting Daikatana pak files, Comanche 3 res files and Blood rff files.

The format of Daikatana pak files and its compression algorithm I analyzed myself. The decompressor himself wrote, which was quite easy, and the compressor, which turned out to be much more difficult. I am not strong in compression algorithms, so the compressor works rather slowly, but compresses it better than the compressor of the developers. Unpacking and packaging was implemented on September 15, 2002, and a more efficient version of the packer was implemented on October 20, 2002.

The format of Comanche 3 res files I also analyzed myself. The difficulty of analyzing this format was that the resource names in it were encrypted, so just through the eyes finding file names proved difficult.

Then I had a self-described program that allowed me to find in an arbitrary file the files contained in it by their signatures. For example, the .wav and .avi files were based on the RIFF signature (plus additional checks), the PCX files were based on their signature, and so on. Using this program, I found the 3 starting point of several files in the Comanche res file. Next to them, I saw their dimensions and some displacements. And there were also fields with obscure content. I wrote a program that gave me a directory of all resources and was able to unpack them into files whose names were compiled from the sequence number of the resource.

Next, I noticed in those obscure records that the last bytes are often the same and assumed that this was the result of a byte encryption with a value of 0 by an XOR operation. I thought there was usually an extension at the end of the file name and found resources whose format I know. So I recovered a four-byte encryption key that was used three times to encrypt a 12-byte file name. The first program was written on February 09, 2003 and was only able to unpack resources.

With rff-files Blood everything turned out to be both easier and more complicated. I found information about the file encryption algorithm on the Internet, but it didn 't fit all the rff files I found. I found several different versions of the BARF utility to create new files for Blood and tried to form new files with them. So I found three different formats of rff files, the unpacking and packaging of which I realized. However, the game did not want to work with native files processed by unpacking and packaging. Eventually I implemented storing and downloading metadata rff files when they were unpacked and packed respectively. The reception worked and Blood began to work with the re-collected files.

With the rest of the formats, things were easier. Some I analyzed myself, about some read on the Internet.

The archive with the original texts of the program can be downloaded here. Immediately there is a text file named ideas.txt, in which I recorded ideas and noted the stages of program development.

(C) 2010-2013 Vladimir Alekseyevich Stupin <vladimir@stupin.su>

The program is distributed under the GPL 3 license.
