13-09-2010

 Implemented a packer/unpacker for Duke Nukem 3D (grp. c).

 It should also be suitable for the following games:
 * Blood
 * Shadow Warrior
 * Redneck Rampage

14-09-2010

 Implemented packers/decompressers for
 Dune 2: The Building of Dynasty (pak.c) и
 Star Wars: Dark Forces (gob.c).

 The latter should also be suitable for playing Outlaws.
 
14-09-2010

 Implement validation of resource names. For grp. c, pak. c, and gob. c , these are the usual DOS names:
 up to 8 characters in the name, a period, and up to three extension characters, all uppercase.
 Latin letters, numbers, minus signs, and underscores are allowed.

 Implement a check for overlapping resources.

 Implement a return of the success/failure status where success is not guaranteed.

15-09-2010
 Implemented an unpacker / packer for Quake (pack. c).

 It should also work with resources from other games:
 * Quake 2,
 * Heretic 2,
 * Half-Life, Counter strike, Opposing force,
 * Soldier of fortune,
 * MDK 2.

A new concept of unpacking/packaging programs has been developed.

Packaging plan:
1. Get a list of file names to pack,
2. From the file names, we get resource names,

3. Calculate the size of the header along with the directory (if the directory follows the header directly),
4. Record all resources. At this stage, you must fill in the missing necessary elements of the catalog:
- the offset of the resource, if necessary,
- the size of the resource, if necessary,
- the size of the resource in compressed form, if necessary, and if compression is used, resource type and / or compression type.
5. Write the correct file header and directory, set the offset to the end of the file.

Unpacking plan:
1. Reading the catalog,
2. Fill in the missing fields of the catalog (you can do this at step 1),
3. Unpack resources or print the contents of the catalog or check the integrity and consistency of the catalog.

```c
typedef enum type_e
{
};

typedef struct resentry_s
{
char *name; // Resource name
char *filename; / / File name on disk
 size_t size; // Size of the resource on disk
 size_t compressed; // Size of the resource inside the bundle file
 size_t offset; / / Resource
offset restype_t type; / / Resource type or compression algorithm
} resentry_t;

typedef struct resdir_s
{
size_t number; / / Number of resources in
the resentry_t *dir directory; / / Resource directory
} resdir_t;

/ * Scans the file system, filling the resource directory with file names.
Scanning can be recursive or non-recursive, with or without alphabetical sorting of files
, with or without adding markers for the beginning and end of the next
directory.*/
bool_t xxx_get_list(resdir_t *dir, const char *path);

/ * Fills the directory with resource names that are correct for the given xxx format.* /
bool_t xxx_fill_names (resdir_t *dir);

/ * Calculates the size of the initial part of the file (header and directory, if the directory is not
at the end of the file) for the xxx format.* /
bool_t xxx_get_header_size(resdir_t *dir, unsigned long *header_size);

/ * Packs files starting from the specified offset. When packing
files, the remaining fields are filled in: file offset, source size,
compressed size, and type. Returns the offset offset corresponding to the byte
following the last packed resource. * /
bool_t xxx_pack_files(FILE *file, resdir_t *dir, const char *basepath, unsigned long *offset);

/ * Writes the resource header and directory. If the resource directory must
be located after the resources, then it is written at offset.*/
bool_t xxx_write_dir(FILE *file, resdir_t *dir, unsigned long offset);

/ * Reading the resource directory and filling in the missing fields. * /
bool_t xxx_read_dir(FILE *file, resdir_t *dir);

/ * Extracting resources to separate files. */
bool_t xxx_unpack_files(FILE *file, resdir_t *dir, const char *basepath);

/ * Print the contents of the resource directory. * /
void xxx_print(resdir_t *dir);
```

 A new version of grp.c has been written, using a new standard scheme
 packing/unpacking.

16-09-2010

 The is_dos_filename function is written to check whether
a string is a DOS file name (checking scheme 8.3 and valid characters).

 Designed a new standard packing/unpacking scheme:

Packaging:
```c
/ * Scans the src_path directory for files to pack,
fills in resource names, calculates the size of the header with the directory
(if the directory should be located at the beginning of the file), sets
the current file pointer file to the position where you can start
writing resources. */
bool_t xxx_prepare_dir(FILE *file, resdir_t *dir, const char *src_path);

/ * The pointer in the file must point to the first byte of
a resource.
Packages files listed in the dir directory and located in
the src_path file system directory. Along the way, it fills in the offset of each resource,
its size, compressed size, resource type, or compression method.*/
bool_t xxx_pack_files(FILE *file, resdir_t *dir, const char *src_path);

/ * The pointer in the file must point to the next byte after all resources.
 Goes to the beginning of the resource file, writes the header
filled in the ready resource directory after the header or recorded data.*/
bool_t xxx_write_dir(FILE *file, resdir_t *dir);
```
Unpacking it:
```c
/ * Reads a directory from a resource file, fills in the names of files that
will be used when extracting resources to files. */
bool_t xxx_read_dir(FILE *file, resdir_t *dir);

/ * Print a resource directory filled with the xxx_read_fir function. * /
void xxx_print_dir(resdir_t *dir);

/ * Retrieves all resources from the resource file. */
bool_t xxx_unpack_files(FILE *file, resdir_t *dir, const char *dst_path);
```
 The grp.c program has been rewritten for a new standard packaging/unpacking scheme.
 The program turned out to be very compact, all the logic of the program works
 viewed easily. This is probably the most optimal scheme
 packaging/unpacking. In the future, I will use it.

 The next plan is to build packers / unpackagers
 pak. c
 gob. c
 pack.c
 under the new packaging/unpacking scheme.

 Then you can start implementing
 the vpp.c packers/decompressers (Red Faction,
 you will need to write vpp_unpack_files),
 viv. c (NFS)
 dpk4. c (Starmageddon, without decompressing compressed resources)
 pack2. c (Daikatana,
 for starters without decompressing compressed resources)
 wad2. c (Quake, Half-Life, without converting images)
 wad. c (Doom, Heretic, Hexen, Strife,
 without converting images)

17-09-2010

 Implemented the unpacker / packer pak. c according to the new scheme
 packaging/unpacking.

 Implemented the gob.c unpacker/packer according to the new scheme
 packaging/unpacking. File names in gob are not DOS names,
 for some files, the actual name is as long as
 9 characters. I checked only the full length of the file name
 with the extension - it should not be more than 12 characters.

 Implemented the pack.c unpacker/packer according to the new scheme
 packaging/unpacking. Added a check for the length
 of the file name - the total length along with the directories and extension
 must not exceed 56 characters.

18-09-2010

 Implemented the vpp.c unpacker/packer.

 The dir_pack_files function can be rewritten using
 align files to the page size. This generalized
 this function can be used in all packers.

 You can also combine the dir_get_list and dir_get_rlist functions.
 Use a generalized function with a boolean parameter specified,
 indicates whether to work in the recursive version or in
 the non-recursive one.

 You can combine the mkpath and dir_make_dirs functions by adding
 a boolean parameter that specifies
 whether to work in recursive mode or not.

 Implement a resource overlap check.

19/20-09-2010

 I rewrote the dir_pack_files function, adding functions to align
 the size of the resource in the file to a multiple of the specified one.

 Rewrote the dir_get_list function by adding a boolean parameter - 
 recursion support. If recursion is not supported, but
 a subdirectory is detected, the function fails with an error.

 I refused to combine mkpath and dir_make_dirs, because the resulting
 function would depend on the resdir_t structure, even if it is not
 needed for a non-recursive call. In this case, the mkpath function would
 still have to be left for projects that do not use
 resdir_t, and this would only complicate and increase the project size.

21-09-2010

 Designed the source code for the copressor and decompressor from the old program
 pack2 / v2 as a module pack2_lz. c and pack2_lz. h

 In the evening, I wrote pack2. c. The program seems to be normally unpacking
 resources from disk, but it unpacked the resources packed by itself
 incorrectly - some initial part of the unpacked
 file coincided,and then there was garbage. I couldn't find out what the problem was.

22-09-2010

 In the afternoon, I found an error in the decompression function. It
 unexpectedly shut down without completing unpacking. The reason for this
 was an incorrect shutdown condition. After fixing
 it several times, the unpacked and packed files remain identical,
 this indicates that there are no obvious errors in the packing/unpacking algorithm.

 This time I was interested in something else. My program,
 in the vast majority of cases, compressing resources is better than the program.
 developers of the game, created a larger file. This problem I have
 I haven't decided yet. All checks show that
 my program compressed a total of 23 megabytes more efficiently, only in
 some 90 cases showing a total lag of 251 bytes. But
 nevertheless, the resulting file created by my program turned out to be
 approximately 40 kilobytes more than the original file.
 
23-09-2010

 Calculated the size of the source file using the sum of the compressed resource sizes.
 It was larger than the original file size! Suspecting something was wrong,
 I finally implemented a resource overlap check. 
 There are resource overlaps in the source file . Resources with different
 names that are identical in content are not added again. They refer to data that is already present in
 the file, so two resources refer to the same block.

 Now I want to implement, in addition to checking the overlap of resources, also search
 for duplicate resources that refer to the same block in the file.

 I also want to implement a search for duplicates when adding another file
 and still wipe the nose of the packer who created the original file,
 out of pure sportinovgo interest. In general, it will be useful to be able to create
 compact files where possible (grp, pak, and vpp formats).
 this is not allowed).

 What else is planned?
 wad2/wad3 (Quake, Half Life)
 dpk4 (Starmageddon)
 viv (NFS)
 wad (Doom)


26-09-2010

 Added a lot of checks and diagnostic messages to the binrw.c module

 Implemented the wad23.c module for working with WAD2 and WAD3 files.

28-09-2010

 Added the viv.c module for working with NFS VIV files. I haven't checked it yet.

 I converted the grp.c, gob.c, pak.c, pack.c, pack2.c, and wad23.c modules into plugins,
 and wrote a single program that works with plugins. Each of the plugins
 has a function of "recognizing" its own format. The recognition functions
 that loop through allow you to implement the automatic detection
 of the file format.

 Added vpp.c, viv.c modules to the program. Wrote a new main function with
 a new logic for processing options and new options.

29-09-2010

 I made some sketches for the piconv program: I wrote a function for setting the format
 storing colors by the mask of each of the components, the function of converting
 colors from one format to another. Debugging is also required in
 case the component is not used.

 Wrote the s_pathname and s_nameext functions in the binrw.c module. Used
 the new function in main.c of the puptool program.

 In the plans, as before:
 IWAD, PWAD - Doom & Co
 DPK4-Starmageddon
 Added to the plans:
 RES-Comanche 3
 RFF - Blood
 DAT - Fallout
 DAT - Fallout 2

30-09-2010

 Added the rff.c module. Unpacking and packaging work fine, but
 the game uses the entry.unknown2 field as resource IDs.
 The game searches for many resources not by name, but by ID. Because of this
 , simply wrapping files doesn't have the desired effect. To make the game work,
 you also need to restore the value of this field. To do this
 , when exporting resources, you also need to create one special file with the names
 of resources and their numbers, and when importing, search for this file and read
 resource IDs from it.

01-10-2010

 Developed a new concept for the resdir.c library, now called
 restable.c. In each plugin, you need to add two simple functions:
 get_resname and get_filename, which will convert
 the file name to the resource name and return it. If the resulting resource name is not
 correct for this format, then the resource name is returned instead
 NULL. The same goes for get_filename.
```c
 void get_resname(char **resname, const char *filename);
 void get_filename(char **filename, const char *resname);
```
 If necessary, these functions can analyze or fill
 in additional fields, such as in the wad23.c module.

 You should also use the ferror function to analyze all
 read-write errors in a single logically complete structure: header, record
 in the resource directory or the entire directory.

 To read numbers from a file, you need to rewrite the freadXe and fwriteXe functions
 so that they do not analyze read/write errors. All
 read/write errors should be analyzed by the parent functions using
 the ferror function.

 When reading / writing structures, you should use grouping
 fields into structures, but read the fields one at a time, using special functions
 for reading/writing fields of various types. 
 
 All these changes will make the program more compact and
 more conceptually integrated.

02-10-2010

 Ported to the restable library and the new plugin system plugins
 grp and gob.

 The next change you can make in the plugin system is
 to add the fill_resname and fill_filename functions to the plugin. fill_resname
 will be called for each of the files in the table immediately after calling
 the fill_entries function. This function will not only convert
 the file name to the resource name, but also check that the resource name is correct for
 this bundle file. fill_filenames will be called for each
 resource in the table immediately after the read_dir function.

 Redesigned the plugin system with the introduction of the fill_name and
 fill_filename, as well as the page fields. Ported the grp, gob, and pak modules to the
 new plugin system.

Comparison of new and old program sizes:
New:
991 binrw. c
80 binrw. h
325 restable. c
69 restable. h
134 grp. c
21 grp. h
159 gob. c
21 gob. h
158 pak. c
21 pak. h
373 main. c
2352 total
Old:
991 binrw. c
79 binrw. h
494 resdir. c
42 resdir. h
160 grp. c
16 grp. h
180 gob. c
16 gob. h
175 pak. c
16 pak. h
457 main. c
2626 total

The comparison of main modules is not entirely fair, since the old program has a larger
table of plugins.

 In the future, you can add additional
 functions to the plugin system to save additional information about files to a text
 file and to restore this information from a text file.

 This functionality will be used for unpacking/packing
 rff and wad2 / wad3 files. 

03-10-2010

 Ported the viv.c module to the new plugin system and restable, at the same time fixing it (added
 alignment of resources to an offset multiple of 4, corrected the calculation of the directory size).

04-10-2010

 Convert the rt_realloc and rt_add_filename functions to the rt_set_number and rt_add_entry functions:

```c
/ * Returns TRUE if successful, sets rt->number = number, and
clears all fields of all rt->entries */
bool_t rt_set_number (restable_t *rt, uint32_t number);

/ * Returns TRUE on success, increments rt - >number, and clears the added
record. The last record added is empty. */
 bool_t rt_add_entry(restable_t *rt);
```

 Ported the vpp.c module to the new plugin system and restable.

 You can also unify checking the validity of a resource name. 
 You can leave out checking DOS file names, but the rest of the checks should be reduced
 to two simple rules: checking the maximum length of the resource name and
 checking whether each character belongs to the set of characters allowed for this
 format.

 Ported the pack.c module to the new plugin system and restable.

 Ported the pack2.c module to the new plugin system and restable.

 New idea: instead of large and similar functions
 xxx_read_resources and xxx_write_resources write smaller functions:
 xxx_read_resource and xxx_write_resource, and put the loop for extracting / adding
 resources in the pack and unpack functions.
```c
 bool_t rt_read_resource(resentry_t *re);
 bool_t rt_write_resource(resentry_t *re, uint32_t page);
```
 This solution will allow you to perform, for example, selective
 resource extraction in the future.

05-10-2010

 Ported wad23. c to the new plugin system and restable. c.

 Rewrote string functions from the binrw.c module so that they now
 additionally report an error, returning FALSE.

 Added the strnlower and strnupper functions to the binrw.c module.

 I rewrote the program so that it now uses the rt_set_number and rt_add_entry functions
 to add items to the
 resource table.

06-10-2010

 I wrote the freadf and fwritef functions, rewrote all modules to use
 the new functions. The program has been reduced from 38 kilobytes to 32. I assume,
 that the decrease is due to a sharp reduction in the number and volume
 of diagnostic messages.

 On the contrary, the project volume in rows has increased (surprisingly).

07-10-2010

 I wrote the res.c module for the RES file of the game Comanche 3. I was tormented. You need
to check on the game.

 Encrypting names is bullshit, because I figured it out back when
 I was playing a game (it was 09-02-2003).

 One of the problems with the resource file is a dummy resource named
 \xD2OOT, whose offset field is equal to the size of the header of the file with
 the directory, and its size field is set to 0.

 The second problem is that before each resource
 , information about the next resource is recorded, but in the last resource
 , information is recorded not about a fictitious resource, but about the present one following it.

 The third suspicious place is 16 null bytes, which for some reason are not allowed.
 added at the end of the file.

 The fourth problem is that the resources are C3.SAV and SETUP.MDMs
 are already found twice in the RES file. They are the same size and follow
 each other.

 We plan to implement the following modules:
 DPK4-Starmageddon
 IWAD, PWAD - Doom & Co
 RFFP, RFFC-Blood (port to restable and add
 saving and restoring resource IDs and types
)
 DAT-Fallout
 DAT - Fallout 2
 LABN - Outlaws

 I tested the res.c module, fixing a bunch of bugs along the way.
 Comanche 3 started working with the resource file I collected.

08-10-2010

 I wrote the dpk4.c module and added support for decompression and compression
 using the zlib library. Unfortunately, not all resources are extracted,
 and after compression, the file size increases as much as 2 times compared to the source file from
 the game distribution. There's no point in compressing it?

 I looked at the information about the file created by my program - not a single
 resource was compressed. Added diagnostics of compression errors and found
 an error in calculating the space for compressible data. Fixed an error -
 now the compressed file size is almost equal to the original one.

 I looked at information about incorrectly uncompressed files - their compressed
 size was equal to the uncompressed one. Removed decompression of resources whose decompressed
 size is equal to the compressed size - made them extracted
 in their original form. Decompression was performed without errors. The dpk4.c module is
 fully debugged.

 The game started with the file created by my program.

10-10-2010

 Tried to implement dat.c module for unpacking and packaging
 DAT files of the Fallout game. The file structure is not trivial, and
 the LZSS compression algorithm used in DAT files is quite rare.

11-10-2010

 Added support for writing and reading "sn" strings to the format string.

 In this case, the length of the string to be read is determined by the number
 whose pointer goes directly after the pointer pointer to the string.
 The length of the recorded string is taken from the number following
 a pointer to the string being written.

 Using the same system, I added support for the format strings "cn"and " zn".

 Added the dat2.c module that supports Fallout 2 DAT files.
 Verification showed that Fallout 2 does not notice file substitution.

 Ported the rff.c module to restable and the new module system.

12-10-2010

 I came up with a method that can be used to exclude duplicate
 files. You can add an additional field to resentry_t
 int32_t copyof, which will record the file number
 that matches the contents of this file. For files
 that do not have duplicates or the source file from the matching group
, the index -1 is placed in this field.

 After filling in the restable_t structure with information about
 the directory structure, you can go through all the files and compare the contents
 of files of the same size. For files where duplicates are found
 , you can enter the number of the first file in this field, which matches
 the next ones. When writing resources with the add_resources function,
 this field will be taken into account and files whose copyof field
 is greater than zero will not be added, but the offset, size, compression
 , and compressed fields will be filled in with copies of these fields from the original file.

 I also conceived a new systematic structure for DAT files.
 A little cumbersome, but understandable. Structures that will be
 the data inside the module can be used independently of
 the restable_t structure in a separate program, if you need
 to write one.

 The main snag in supporting the DAT file format of Fallout is still
 it consists of writing a decompressor and a compressor in the LZSS format.

 I downloaded the f1undat source code, which has functionality for unpacking
 resources. The source code of the decompressor, however, is mostly
 in Assembler.

13-10-2010

 I found a resource with a large number of examples of implementing an lzss compressor
in C.

 I wrote the rt_check_overlaps function, which searches for copies of resources
 and overlapping resources. During operation, the function fills
 in a new resentry_t field-the copyof field, which contains the number
 of the resource that this resource is a copy of. If the resource is not
 a copy, then -1 is placed in this field.

 A check on the pak1.pak file from Daikatana showed that the function
 copes with the work assigned to it.

 Now you can write a file comparison function and a search function
 duplicate files, which will fill
 in the copyof field of each record in the same way. Then you can add a special behavior
 to the add resources function so that it doesn't add twice
 the same content of different resources, but only added a link
 to the previously added resource-the original one.

 I wrote the functionality of combining duplicate files, registered it in
 all modules that allow you to combine resources.

 I tested the function on the pak1.pak file of the Daikatana game. Excellent,
 my program finally beat the Daikatana packer:
 Original file size: 167129921
 Size of the repacked file: 164899416
 The total savings are about 3 megabytes.

 Testing combining duplicates using the example of the data.dpk file
 Starmageddon 2
 Original: 288025136
 Repacked: 276083021
 Total savings - almost 12 megabytes.


 You can add an additional feature field to the plugin_t structure
 combine resource duplicates.

 You need to remove the *_add_resources subfunctions from the *_add_resources functions,
 and the resource alignment and resource loop will be removed.
 to the main module. The same can be done with functions
 *_extract_resources, that is, remove the *_add_resource subfunctions from them,
 and move the resource loop to the main module.

 You can add two additional options to the main module:
 --nocompress/--compress and --nomerge/--merge. Alternatively, you can
 make one option --fast/--finish, which will disable or
 enable resource compression if it is supported by this format and
 merge duplicates if duplicate merging is possible for this
 format.

14-10-2010

 Ported the program to a new plugin system:
 instead of the functions add_resources(restable_t *rt, uint32_t page)
 , add_resource(restable_t *rt, uint32_t i) is used,
 instead of the extract_resources(restable_t *rt, uint32_t page)
 functions, extract_resource(restable_t *rt, uint32_t i)
 is used. The merge boolean field is added to the structure.

 Work on finding duplicate files and resources and aligning
 resources when adding them has been moved to the unpack, pack functions,
 print. Duplicates are found and merged only
 if the merge field of the plugin_t structure is true.

 I wrote a function for comparing data in ring buffers ringcmp,
 Using it, I wrote a function for finding the best match
 of data blocks for algorithms of the LZ77 group. All this is
 in the ring.c module

 I wrote a new function that is more resource-intensive, but also more systematic:
 bool_t dat_read_dir(restable_t *rt);

 I wrote the dat_to_rt function and the dat_from_rt function. The second one is already sufficient
 to write the correct dat_prepare_dir function, but before writing
 for the DAT header, I want to sort paths and filenames alphabetically.

15-10-2010

 I wrote functions for sorting the dat_t - dat_sort structure, for
 calculating the size of a directory written to a DAT file-dat_prepare_dir,
 and for writing a directory to a DAT file-dat_write_dir.

 I wrote the dat_decmpress function and put it in the dat_lzss module. c
 Resource compression is not supported yet.

 Debugging failed - Fallout doesn't work with the files I collected.
 Fallout shows the "wait" screen and exits.

16-10-2010

 I tested the dat.c. module not without problems, but managed to bring it
 to working condition. The main problem was that
 the names of directories and resources are written in upper case. If the names are
 directories and resources are written in lowercase, then Fallout starts
 as if nothing had happened, although the files from the game's distribution contain all the names
 directories and resources are written in uppercase. I can't
 find any explanation for this.

17-10-2010

 I rewrote the freadf and fwritef functions, as well as all the others on which
 they are based. The new functions are called readf and writef. Format string
 it has become more feature-rich, and the functions themselves are more direct.

 For example, the readsz function, a replacement for the s_freadz function, now reads the file
 in order and does not return to what it has already read, changing the
 buffer size of the baud string as it reads. In other words, it is now suitable for reading files
 with strictly sequential access.

 Another example is that instead of the frwite_zeros and fread_bytes functions, fwritec and freadc are now
 used, which, when passing a null pointer
 to the read/write buffer, write zeros or read data "to the void".

 The readf and writef functions introduce argument length specifiers
 n and N. The first is a number with a length, the second is a pointer to a number with a length.

19-10-2010

 I wrote the binup.c - binary unpack/pack module, in which I implemented
 analogs of functions from the binrw2.c module, only these functions are called
 pack/unpack and work with a memory buffer, not a file.

 The rff.c module was rewritten using binup. c. Its code
 has become much smaller, cleaner, and more visual. The next
 planned step is to write a text.c module for parsing
 text files to recover the value of the type field from
 a text file. 

 Then the binrw.c, binrw2.c, and binup.c modules were combined into one
 large bin.c module

20-10-10

 Added the scans and strtrim functions to the bin.c module.

 I wrote the meta.c module for loading and saving metadata.

 Added the --savemeta and --loadmeta modes to the main.c module,
 added the --meta option to the --pack and --unpack modes.

 I tested the written functionality on the blood.rff file, it seems
 to work. We need to check on the game itself.

 The written code is quite dirty and needs to be checked.

 I also rewrote the s_name and company functions using
 the strrchr function. I haven't tested it yet - I put it in the newnpe.c module

 Blood with the file collected by my program does not start.

21-10-10

 I wrote a simple template for the ipwad.c module.I haven't made any attempt to
 convert resource names yet.

22-10-10

 Finally, I wrote the ipwad.c module. Whether brains work better
 we started, whether past developments helped, but I added the moodle
 up to working condition today until the end. The module turned out to be quite
 dirty, but working.

 Interestingly, in the original doom file.wad
 resources with the same name are encountered several times. So far, I
've only seen such tricks in the Commanche 3 RES file.

 List of files with the same name:
 dpbarexp
 dpbdcls
 dpbdopn
 dpbgact
 dpbgdth1
 dpbgdth2
 dpbgsit1
 dpbgsit2
 dpbrsdth
 dpbrssit
 dpclaw
 dpdmact
 dpdmpain
 dpdorcls
 dpdoropn
 dpfirsht
 dpfirxpl
 dpgetpow
 dpitemup
 dpitmbk
 dpnoway
 dpoof
 dppdiehi
 dppistol
 dppldeth
 dpplpain
 dppodth1
 dppodth2
 dppodth3
 dppopain
 dpposact
 dpposit1
 dpposit2
 dpposit3
 dppstart
 dppstop
 dppunch
 dprlaunc
 dprxplod
 dpsawful
 dpsawhit
 dpsawidl
 dpsawup
 dpsgcock
 dpsgtatk
 dpsgtdth
 dpsgtsit
 dpshotgn
 dpslop
 dpstnmov
 dpswtchn
 dpswtchx
 dptelept
 dptink
 dpwpnup
 dsbarexp
 dsbdcls
 dsbdopn
 dsbgact
 dsbgdth1
 dsbgdth2
 dsbgsit1
 dsbgsit2
 dsbrsdth
 dsbrssit
 dsclaw
 dsdmact
 dsdmpain
 dsdorcls
 dsdoropn
 dsfirsht
 dsfirxpl
 dsgetpow
 dsitemup
 dsitmbk
 dsnoway
 dsoof
 dspdiehi
 dspistol
 dspldeth
 dsplpain
 dspodth1
 dspodth2
 dspodth3
 dspopain
 dsposact
 dsposit1
 dsposit2
 dsposit3
 dspstart
 dspstop
 dspunch
 dsrlaunc
 dsrxplod
 dssawful
 dssawhit
 dssawidl
 dssawup
 dssgcock
 dssgtatk
 dssgtdth
 dssgtsit
 dsshotgn
 dsslop
 dsstnmov
 dsswtchn
 dsswtchx
 dstelept
 dstink
 dswpnup

 This suggests the idea of trying to make a search function
 duplicates of resource names.

09-11-2010

 Added resource timestamp display to the rff.c module.

13-11-2010

 Added the meta and time Boolean fields to the plugin structure,
 the save_meta and load_meta functions.

 Redesigned the unpack, pack, print, and savemeta functions, taking into account
 the functionality of plugins for loading and saving metadata.
 Removed the loadmeta function.

 Implemented functions for transferring the modification
 time of a file from a batch file to a file and from a file to a batch file:
 rt_get_timestamp and rt_set_timestamp

 I checked the transfer of time stamps using the example of an rff file.

29-12-2010

 Adapted the lzss.c utility from Haruhiko Okumura to the module
 lzss.c.

 I changed the pack2_lz.c module into the c_pack2.c
 module, created the c_zlib.c, c_lzss.c modules. The essence of the change is,
 that now all compression/decompression functions are brought
 to a single interface:
```c
 size_t dsize(size_t ssize);

 bool_t compress(unsigned char *s, size_t ssize, unsigned char *d, size_t *dsize, int level);
 or
 bool_t compress(unsigned char *s, size_t ssize, unsigned char *d, size_t *dsize);

 bool_t decompress(unsigned char *s, size_t ssize, unsigned char *d, size_t dsize);
```
 I wrote the c_dat.c module using c_lzss. c. Tested it and it works.

11-01-2011

 In the RFF format header, in the version field, the lower two bytes in all
 the file samples I examined take the following values::
 2 and 0 are the previously named Plain RFF format,
 3 and 1 are the previously named Crypted RFF format,
 and 3 and 0 are the format created by one of the available versions of the BARF program.
 
 According to this, I named these formats rff20, rff30, rff31.
 
 Today I added support for the rff30 format, which differed from rff31
 only in the way the directory was encrypted, and
 renamed all modules accordingly.

17-01-2011

 Finished loading metadata. I found that blood.rff has resources with
 the same names:
 BAT1D1. SEQ
 BEST1D1.SEQ
 BEST2D1.SEQ
 CERB1E1.SEQ
 CULT1D3B.SEQ
 CULT2E1.SEQ
 GOST1M1.SEQ
 HAND1D1.SEQ
 PLAY1D1.SEQ
 PLAY1M1.SEQ
 PLAY1M4.SEQ
 POD1CLOS.SEQ
 POD2CLOS.SEQ
 PRIS1D1.SEQ
 RAT1D1.SEQ
 SPID3A2.SEQ
 SPID3D1.SEQ
 SPID3D2.SEQ
 SPID3D3.SEQ
 SPID3I1.SEQ
 SPID3M1.SEQ
 SPID3M2.SEQ
 TBOG1D1.SEQ
 TENT1D2.SEQ
 TENT1DOW.SEQ
 TENT2D2.SEQ
 TENT2DOW.SEQ

18-01-2011

 I wrote the s_sprintf, rt_rename, and is_equal_blocks functions in order to use them
 in the future to organize correct processing of resources with the same names.

 Renamed the strupper, strlower, strnupper, and strnlower functions to s_strupper, s_strlower, s_strnupper,
 and s_strnlower, respectively.

19-01-2011

 Added the s_let function, converted the s_strcpy, s_strncpy, s_strcat, and s_strncat functions to the sn_strcpy, sn_strncpy, sn_strcat, and sn_strncat
 functions.

 Based on s_let and sn_strcpy, sn_strncpy, sn_strcat, sn_strncat implemented the old
 functions s_strcpy, s_strncpy, s_strcat, s_strncat.

 Converted the s_sprintf function to the snv_sprintf function.

 Based on s_let and snv_sprintf, I implemented the s_sprintf function.

 Added two regression tests for the s_sprintf function. All redesigned functions
 have successfully passed the regression testing procedure.

27-01-2011

 Changed the functions s_uppath, s_path, s_pathname, s_name, s_nameext, s_ext to the
 functions sn_uppath, sn_path, sn_pathname, sn_name, sn_nameext, sn_ext.

 Based on s_let and sn_uppath, sn_path, sn_pathname, sn_name, sn_nameext, sn_ext
 implemented the functions s_uppath, s_path, s_pathname, s_name, s_nameext, s_ext.

 The regression tests were completed successfully.

01-02-2011

 I wrote and almost debugged the rt_fix_loaded function, which should
 search for duplicates, search for links to identical blocks, search
 for block intersections, and search for identical file names.

 Rewrote the function of checking the rt_fix directory instead of rt_fix_loaded. I did
 it on the principle of the simpler, the better. It really turned out better - the volume
 is smaller, the complexity is lower, and the speed of work has not changed by eye.

 Cleaned up: removed rt_fix_loaded, rt_search_overlaps, rt_search_doubles,
 rt_sort, etc. The project size after cleaning again became less than 10000 lines.

 I tested the disassembly and assembly of blood. rff, and a file of the same size is being assembled.
 The number and order of resources is preserved.

09-02-2011

 In the pack2 compression algorithm, the control byte with the value 0xFF is used
 as an indicator of the end of the compressed stream. Some time ago, I
 fixed the decoder accordingly, and today I fixed it
 the encoder.

 Combined all the *_fadd and *_fextract functions into the c_fadd and c_fextract functions.

 There was an idea to change the logic a little. c_fadd, if the data was not
 compressed, should return a compressed size equal to zero, not equal
 to the uncompressed size. Did.

08-11-2011

 Analysis of record type and extension matches in an RFF file:

 type ext

 0 MNU 0 0000
 1 TXT, SFX, MID 1 0001
 16 MAP, RAW, TMB 0 + 16 0000
 17 WAV, KVX, QAV 1 + 16 0001 Other QAV
 20 QBM, QFN 4 + 16 0100
 21 SEQ 5 + 16 0101
 24 FLU, TLU, DAT, CLU 8 + 16 1000
 25 PLU, PAL, QAV 9 + 16 1001 On-screen QAV

11-01-2013

 On the computer, I found all the pup directories and performed a comparison. As a result
 , there are two different directories left. The program was not built in both directories.
 Fixed the program in this directory and built it.

 When studying the source code, I was surprised that rff files were
 fully supported. Tested on three rff31 files from blood: unpacked and
 packed back. Changed the collected files in the game folder. The game
 continued to work after the substitution.

 Apparently, the IWAD/PWAD support plugin remains among the unfinished functions.
 I doubt I can bring it to mind.

