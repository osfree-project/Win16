/*

.GRP Group File Format Overview (3.1)

This topic describes the format of group files used by the Microsoft Windows operating system. A group file contains data that 
Microsoft Windows Program Manager (PROGMAN.EXE) uses to display the icons of the applications in a group, start the 
applications in a group, and open related documents. 

Organization of a Group File

The first element in a group file is the group-file header. The data in the group-file header includes an identifier, a count of bytes, 
a count of items in the file, and information that the system uses to display group icons. 

The group-file header is followed by one or more entries that contain item data describing the icon of an application. These 
entries include the coordinates that the system uses to display the icon; the count of bytes in the header, AND mask, and XOR 
mask for the icon; and the offset to the header, AND mask, and XOR mask for the icon. 

The item data entries are followed by entries that contain the color data for the application icons. For more information about 
these entries, see Graphics Device Interface Overview. 

For Windows version 3.1, the icon data is followed by tag data. The tag data contains information that Program Manager uses 
when it displays the Program Item Properties dialog box. This data identifies the directory in which the application is stored and 
the shortcut key (if one exists). It also specifies the state of the Run Minimized box. 

Group-File Structures

This topic uses C structures to depict the organization of data within a group file. These structures were created solely to show 
the organization of data in a resource; they do not appear in any of the include files shipped with the Microsoft Windows 3.1 
Software Development Kit (SDK). 

Group-File Header

The group-file header contains general information about the group file. The GROUPHEADER structure has the following form: 

*/

#pragma pack( push, 1 )

struct tagGROUPHEADER {
  char  cIdentifier[4];		// Identifies an array of 4 characters. If the file is a valid group file, this array must contain the string "PMCC". 
  WORD  wCheckSum;		// Negative sum of all words in the file (Means: sum of all words in file, including wCheckSum, must be zero)
  WORD  cbGroup;		// Size of the group file, in bytes, excluding TAGDATA (Can be treated as TAGDATA offset)
  WORD  nCmdShow;		// Whether Program Manager should display the group in minimized, normal, or maximized form.
  RECT  rcNormal;		// Coordinates of the group window (the window in which the group icons appear). It is a rectangular structure.
  POINT ptMin;			// Coordinate of the lower-left corner of the group window with respect to the parent window. It is a point structure.
  WORD  pName;			// Offset from the beginning of the file to a null-terminated string that specifies the group name.
  WORD  wLogPixelsX;		// Horizontal resolution of the display for which the group icons were created.
  WORD  wLogPixelsY;		// Vertical resolution of the display for which the group icons were created.
  BYTE  bBitsPerPixel;		// Format of the icon bitmaps, in bits per pixel. Error: as WORD in SDK https://jeffpar.github.io/kbarchive/kb/086/Q86334/
  BYTE  bPlanes;		// Count of planes in the icon bitmaps. Error: as WORD in SDK https://jeffpar.github.io/kbarchive/kb/086/Q86334/
  WORD  wReserved;		// Must be 0
  WORD  cItems;			// Number of ITEMDATA structures in the rgiItems array. This is not necessarily the number of items in the group, because there may be NULL entries in the rgiItems array.
};

/* 
Following are the members in the GROUPHEADER structure: 

This member can be one of the following values: 

Value	Flag

0x00	SW_HIDE 
0x01	SW_SHOWNORMAL 
0x02	SW_SHOWMINIMIZED 
0x03	SW_SHOWMAXIMIZED 
0x04	SW_SHOWNOACTIVATE 
0x05	SW_SHOW 
0x06	SW_MINIMIZE 
0x07	SW_SHOWMINNOACTIVATE 
0x08	SW_SHOWNA 
0x09	SW_RESTORE 

rgiItems[cItems]	Specifies an array of ITEMDATA structures. (@todo offset of item or array of items???)

Item Data

The item data contains information about a particular application and its icon. The ITEMDATA structure has the following form: 

*/

struct tagITEMDATA {
    POINT pt;			// Coordinates for the lower-left corner of an icon in the group window. It is a point structure. 
    WORD  iIcon;		// Index value for an icon. This value indicates the position of the icon in an executable file. 
    WORD  cbResource;		// Count of bytes in the icon resource, which appears in the executable file for the application. 
    WORD  cbANDPlane;		// Count of bytes in the AND mask for the icon.
    WORD  cbXORPlane;		// Count of bytes in the XOR mask for the icon. 
    WORD  pHeader;		// Offset from the beginning of the group file to the resource header for the icon. 
    WORD  pANDPlane;		// Offset from the beginning of the group file to the AND mask for the icon. 
    WORD  pXORPlane;		// Offset from the beginning of the group file to the XOR mask for the icon. 
    WORD  pName;		// Offset from the beginning of the group file to a string that specifies the item name.
    WORD  pCommand;		// Offset from the beginning of the group file to a string that specifies the name of the executable file containing the application.
    WORD  pIconPath;		// Offset from the beginning of the group file to a string that specifies the path where the file with icon resource is located.
};

/*

Tag Data

The tag data contains general information used to display the Program Item Properties dialog box. The TAGDATA structure 
has the following form: 

*/

struct tagTAGDATA{
    WORD wID;			// type of tag data.
    WORD wItem;			// index to the item the tag data refers to. If the data is not specific to a particular item, this value is 0xFFFF.
    WORD cb;			// size of the TAGDATA structure, in bytes.
    BYTE rgb[1];		// an array of byte values. The length of this array can be found by subtracting 6 from the value of the cb member.
};

/*

wID	can have one of the following values: 

Value	Meaning

0x8101	Array at which the rgb member points is a null-terminated string that identifies the path for the application. 
0x8102	Array at which the rgb member points is a 16-bit word value that identifies the shortcut key specified by the 
user. 
0x8103	Minimized version of the item is displayed. If this value is specified, the array to which the rgb member 
points is not present in the structure and the value of the cb member is 0x06. 


*/

struct tagICONRESOURCEHEADER {
	int xHotSpot;    // Should be 0
	int yHotSpot;    // Should be 0
	int cx;          // Icon width
	int cy;          // Icon height
	int cbWidth;     // Bytes per row accounting
					// for WORD alignment
	BYTE bPlanes;    // Count of planes
	BYTE bBitsPixel; // Bits per pixel
};

#pragma pack( pop )
