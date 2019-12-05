Unpacker and Game Resource Packer PUP
=====================================

About
-----

The program is called PUP - Packer/UnPacker (the word pup can also be translated from English as "puppy"). The program has several modes of operation:


Usage
-------------
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

Building
--------

    $ ./autogen.sh

    $ ./configure --prefix=PREFIX

    $ make

    $ make install


Status
------

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

List of formats to be implemented:

    Unsupported plugins:
    pod     POD-files of type:
            POD1: Terminal Velocity, Fury3, Hellbender, Monster Truck Maddness 1 & 2,
                  CART Precision Racing
            POD2: Nocturne, Blair Witch Volume 1: Rustin Parr, 4x4 Evo 1 & 2
            POD3: Fly! 2, Blood Rayne 1 & 2, BlowOut, Aeon Flux, Metal Slug Anthology
            POD4: The King of Fighters Collection: The Orochi Saga, Samurai Shodown Anthology
            POD5: Ghostbusters: The Video Game
            EPD/Extended POD: Fly!

Known issues
------------


Credits
-------

- [Jon Daniel][jopadan/pup]
- [Vladimir Stupins][stupin/pup]

[jopadan/pup]: https://github.com/jopadan/pup "Jon Daniel"
[stupin/pup]: https://stupin.su/git/pupin/pup "Vladimir Alekseyevich Stupins"

Related projects with similar features and information about the POD file format:
- [physfs][]
- [podextract][]
- [jtrfp][]
- [DragonUnPACKer][]
- [Ghostbusters Unpack][]
- [Game Extractor][]

[physfs]: https://github.com/jopadan/physfs
[podextract]: https://github.com/ghoost82/podextract 
[jtrfp]: https://github.com/jtrfp/jtrfp
[DragonUnPACKer]: https://github.com/elbereth/DragonUnPACKer
[Ghostbusters Unpack]: http://svn.gib.me/public/ghostbusters/trunk/
[Game Extractor]: http://www.watto.org

(C) 2010-2013 Vladimir Alekseyevich Stupin <vladimir@stupin.su>

The program is distributed under the GPL 3 license.
