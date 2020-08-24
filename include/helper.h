/** 
 * Amal Khan 1033360
 * Assignment 1 CIS2750
 * Winter 2020
 * Prof. Denis Nikitenko
**/



#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlschemastypes.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"




// Function to create a SVGimage object
SVGimage* createSVGStruct(char namespace[256], char title[10], char description[256]);



// Function to create an attribute object
Attribute* createAttribute(char* name, char* value);

// Function to clone an attribute object
Attribute* cloneAttribute(Attribute* att);



// Function to create a rectangle object
Rectangle* createRectangle(float x, float y, float width, float height, char units[50]);

// Function to clone a rectangle object
Rectangle* cloneRectangle(Rectangle* rectangle);



// Function to create a circle object
Circle* createCircle(float cx, float cy, float r, char units[50]);

// Function to clone a circle object
Circle* cloneCircle(Circle* circle);



// Function to create a path object
Path* createPath(char* data);

// Function to clone a path object
Path* clonePath(Path* path);



// Function to create a group object
Group* createGroup();

// Function to clone a group object
Group* cloneGroup(Group* group);



// Function to parse a SVGFile and organize it contents
SVGimage* parseSVGFile(xmlNode * node, SVGimage* svg);

// Function to parse a SVG node's properties
void parseSVGNode(xmlAttr *node, SVGimage* svg);

// Function to parse a rectangle node's properties
void parseRectangle(xmlAttr *node, List* l);

// Function to parse a circle node's properties
void parseCircle(xmlAttr *node, List* l);

// Function to parse a path node's properties
void parsePath(xmlAttr *node, List* l);

// Function to parse a group node's properties
void parseGroup(xmlNode* n, List* l);



// Function to recursively get all rectangles in a group and its subgroups
void rectanglesFromGroup(List* l, Group* g);

// Function to recursively get all circles in a group and its subgroups
void circlesFromGroup (List* l, Group* g);

// Function to recursively get all paths in a group and its subgroups
void pathsFromGroup (List* l, Group* g);

// Function to recursively get all groups in a group and its subgroups
void groupsFromGroup (List* l, Group* g);



//Dummy delete function that does nothing
void dummyDelete(void *a);


//******************************A2 FUNCTIONS*******************************//
//******************************A2 FUNCTIONS*******************************//
//******************************A2 FUNCTIONS*******************************//

// functions that check a list of structs against the requirements in svgparser.h
bool checkSVG(SVGimage* svgimage);
bool validateListOfGroups (List* groups);
bool validateListOfPaths (List* paths);
bool validateListOfCircles (List* circles);
bool validateListOfRectangles (List* rectangles);
bool validateListOfOtherAttributes (List* otherAttributes);

// functions that check a single struct against the requirements in svgparser.h
bool validatePath(Path* path);
bool validateCircle (Circle* circle);
bool validateRectangle (Rectangle* rectangles);
bool validateAttribute (Attribute* attribute);
bool validateGroup(Group* group);


// function that compares an xmldoc to a SVG Standards file to see if the xmldoc is valid
bool validateXml(xmlDocPtr xmldoc, char* schemaFile);

// function to convert a svgimage object into a xmldoc struct
xmlDocPtr svgToXml(SVGimage* doc);

// Functions to turn different elements in our SVG object into nodes in an xmldoc
void parseRectanglesWrite(xmlNodePtr xmlnode, List* rectangles);
void parseCirclesWrite(xmlNodePtr xmlnode, List* circles);
void parsePathsWrite(xmlNodePtr xmlnode, List* paths);
void parseGroupsWrite (xmlNodePtr xmlnode, List* groups);


void setRectangleAttribute (Rectangle* rectangle, Attribute* newAttribute);
void setCircleAttribute (Circle* circle, Attribute* newAttribute);
void setPathAttribute (Path* path, Attribute* newAttribute);
void setGroupAttribute (Group* group, Attribute* newAttribute);
void setSVGAttribute (SVGimage* img, Attribute* newAttribute);

bool checkExistingAttributes(List* list, Attribute* newAttribute);