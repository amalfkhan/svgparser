/** 
 * Amal Khan 1033360
 * Assignment 2 CIS2750
 * Winter 2020
 * Prof. Denis Nikitenko
**/

//While iterator template taken from course content


#include <stdio.h>
#include <math.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

#define LIBXML_SCHEMAS_ENABLED



// Function to delete attribute content and free all the memory.
void deleteAttribute(void* data) {
    if (data == NULL){
	    return;
	}

    Attribute* tmp = (Attribute*)data;
    free(tmp->name);
    free(tmp->value);
    free(tmp);
}

// Function to create a string representation of a attribute object.
char* attributeToString( void* data) {
    if (data == NULL){
		return NULL;
	}

    Attribute* tmp = (Attribute*)data;
    char* s = calloc(1024, sizeof(char)+10);
    strcat(s, tmp->name);
    strcat(s, ": ");
    strcat(s, tmp->value);
    strcat(s, "\n");
    return s;
}

// Function to compare two attribute objects.
int compareAttributes(const void *first, const void *second) {
	if (first == NULL || second == NULL){
		return 0;
	}

    Attribute* firstatt = (Attribute*)first;
    Attribute* secondatt = (Attribute*)second;
    char* firststr = attributeToString(firstatt);
    char* secondstr = attributeToString(secondatt);
    int cmp = strcmp(firststr, secondstr);
    free(firststr);
    free(secondstr);
    return cmp;
}



// Function to delete group content and free all the memory.
void deleteGroup(void* data) {
    if (data == NULL){
	    return;
	}

    Group* tmp = (Group*)data;
    freeList(tmp->rectangles);
    freeList(tmp->circles);
    freeList(tmp->paths);
    freeList(tmp->groups);
    freeList(tmp->otherAttributes);
    free(tmp);
}

// Function to create a string representation of a group object.
char* groupToString( void* data) {
    if (data == NULL){
		return NULL;
	}

    Group* tmp = (Group*)data;
    char* s = calloc(64, sizeof(char)+10);
    
    char* list = toString(tmp->rectangles);
    s = realloc(s, strlen(list) + strlen(s) + 64); //check NULL for strlen
    strcat(s, list);
    strcat(s, "\n");
    free(list);

    list = toString(tmp->circles);
    s = realloc(s, strlen(list) + strlen(s) + 64);
    strcat(s, list);
    strcat(s, "\n");
    free(list);

    list = toString(tmp->paths);
    s = realloc(s, strlen(list) + strlen(s) + 64);
    strcat(s, list);
    strcat(s, "\n");
    free(list);

    list = toString(tmp->otherAttributes);
    s = realloc(s, strlen(list) + strlen(s) + 64);
    strcat(s, list);
    strcat(s, "\n");
    free(list);
    
    // recursively add other groups
    if((tmp->groups)->length == 0) {
        return s;
    } else {
        ListIterator iter = createIterator(tmp->groups);
        void* elem;
        
        while((elem = nextElement(&iter)) != NULL) {
            elem = (Group*)elem;
            // s = realloc(s, strlen(s) + 64);
            char* groupstring = groupToString(elem);
            s = realloc(s, strlen(groupstring) + strlen(s) + 64);
            strcat(s, groupstring);
            free(groupstring);
        }

    }
    
    return s;
}

// Function to compare two group objects.
int compareGroups(const void *first, const void *second) {
	if (first == NULL || second == NULL){
		return 0;
	}

    Group* firstgrp = (Group*)first;
    Group* secondgrp = (Group*)second;
    char* firststr = groupToString(firstgrp);
    char* secondstr = groupToString(secondgrp);
    int cmp = strcmp(firststr, secondstr);
    free(firststr);
    free(secondstr);
    return cmp;
}



// Function to delete rectangle content and free all the memory.
void deleteRectangle(void* data) {
    if (data == NULL){
	    return;
	}

    Rectangle* tmp = (Rectangle*)data;
    freeList(tmp->otherAttributes);
    free(tmp);
}

// Function to create a string representation of a rectangle object.
char* rectangleToString(void* data) {
    if (data == NULL){
		return NULL;
	}

    Rectangle* tmp = (Rectangle*)data;
    char* s = calloc(1024, sizeof(char)+10);
    char* c = calloc(24, (sizeof(char)*4)+10);
    
    strcat(s, "RECTANGLE\n");
    strcat(s, "x-cord: ");
    sprintf(c, "%f", tmp->x);
    strcat(s, c);
    strcat(s, "\n");
    free(c);

    c = calloc(24, (sizeof(char)*4)+10); 
    strcat(s, "y-cord: ");
    sprintf(c, "%f", tmp->y);
    strcat(s, c);
    strcat(s, "\n");
    free(c);   

    c = calloc(24, (sizeof(char)*4)+10); 
    strcat(s, "width: ");
    sprintf(c, "%f", tmp->width);
    strcat(s, c);
    strcat(s, "\n");
    free(c);

    c = calloc(24, (sizeof(char)*4)+10); 
    strcat(s, "height: ");
    sprintf(c, "%f", tmp->height);
    strcat(s, c);
    strcat(s, "\n");
    free(c);

    strcat(s, "units: ");
    strcat(s, tmp->units);
    strcat(s, "\n");

    char* list = toString(tmp->otherAttributes);
    s = realloc(s, strlen(list) + strlen(s) + 64);
    strcat(s, list);
    strcat(s, "\n");
    
    free(list);
    return s;
}

// Function to compare two rectangle objects.
int compareRectangles(const void *first, const void *second) {
	if (first == NULL || second == NULL){
		return 0;
	}

    Rectangle* firstrect = (Rectangle*)first;
    Rectangle* secondrect = (Rectangle*)second;
    char* firststr = groupToString(firstrect);
    char* secondstr = groupToString(secondrect);
    int cmp = strcmp(firststr, secondstr);
    free(firststr);
    free(secondstr);
    return cmp;
}



// Function to delete circle content and free all the memory.
void deleteCircle(void* data) {
    if (data == NULL){
	    return;
	}

    Circle* tmp = (Circle*)data;
    freeList(tmp->otherAttributes);
    free(tmp);
}

// Function to create a string representation of a circle object.
char* circleToString(void* data) {
    if (data == NULL){
		return NULL;
	}

    Circle* tmp = (Circle*)data;
    char* s = calloc(1024, sizeof(char)+10);
    char* c = calloc(24, (sizeof(char)*4)+10);
    
    strcat(s, "CIRCLE\n");
    strcat(s, "x-cord: ");
    sprintf(c, "%f", tmp->cx);
    strcat(s, c);
    strcat(s, "\n");
    free(c);

    c = calloc(24, (sizeof(char)*4)+10); 
    strcat(s, "y-cord: ");
    sprintf(c, "%f", tmp->cy);
    strcat(s, c);
    strcat(s, "\n");
    free(c);   

    c = calloc(24, (sizeof(char)*4)+10); 
    strcat(s, "radius: ");
    sprintf(c, "%f", tmp->r);
    strcat(s, c);
    strcat(s, "\n");
    free(c);

    strcat(s, "units: ");
    strcat(s, tmp->units);
    strcat(s, "\n");

    char* list = toString(tmp->otherAttributes);
    s = realloc(s, strlen(list) + strlen(s) + 64);
    strcat(s, list);
    strcat(s, "\n");
    
    free(list);
    return s;
}

// Function to compare two circle objects.
int compareCircles(const void *first, const void *second) {
	if (first == NULL || second == NULL){
		return 0;
	}

    Circle* firstcir = (Circle*)first;
    Circle* secondcir = (Circle*)second;
    char* firststr = groupToString(firstcir);
    char* secondstr = groupToString(secondcir);
    int cmp = strcmp(firststr, secondstr);
    free(firststr);
    free(secondstr);
    return cmp;
}



// Function to delete path content and free all the memory.
void deletePath(void* data) {
    if (data == NULL){
	    return;
	}

    Path* tmp = (Path*)data;
    free(tmp->data);
    freeList(tmp->otherAttributes);
    free(tmp);
}

// Function to create a string representation of a path object.
char* pathToString(void* data) {
    if (data == NULL){
		return NULL;
	}

    Path* tmp = (Path*)data;
    char* s = calloc(1024, sizeof(char)+10);
    strcat(s, "PATH\n");
    strcat(s, "d: ");
    strcat(s, tmp->data);
    strcat(s, "\n");

    char* list = toString(tmp->otherAttributes);
    s = realloc(s, strlen(list) + strlen(s) + 64);
    strcat(s, list);
    strcat(s, "\n");
    
    free(list);
    return s;
}

// Function to compare two path objects.
int comparePaths(const void *first, const void *second) {
	if (first == NULL || second == NULL){
		return 0;
	}

    Path* firstp = (Path*)first;
    Path* secondp = (Path*)second;
    char* firststr = groupToString(firstp);
    char* secondstr = groupToString(secondp);
    int cmp = strcmp(firststr, secondstr);
    free(firststr);
    free(secondstr);
    return cmp;
}


// Function to create an SVG object based on the contents of an SVG file.
SVGimage* createSVGimage(char* fileName) {
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    if (fileName == NULL) {
        return NULL;
    }

    FILE *svgfile;
    if ((svgfile = fopen(fileName, "r")) == NULL) {
        return NULL;
    }
    fclose(svgfile);
    

    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) {
        return NULL;
    }

    SVGimage* svg = createSVGStruct("", "", "");
    root_element = xmlDocGetRootElement(doc);
    svg = parseSVGFile(root_element, svg);
    // SVGimage* svgrtn = parseSVGFile(root_element, svg);
    

    xmlFreeDoc(doc);
    xmlCleanupParser();

    // return svgrtn;
    return svg;
}

// Function to create a string representation of an SVG object.
char* SVGimageToString(SVGimage* img) {
    if (img == NULL){
		return NULL;
	}

    SVGimage* tmp = (SVGimage*)img;
    char* s = calloc(1024, sizeof(char)+10);
    strcat(s, "SVGIMAGE\n");
    strcat(s, "namespace: ");
    strcat(s, tmp->namespace);
    strcat(s, "\n");
    strcat(s, "title: ");
    strcat(s, tmp->title);
    strcat(s, "\n");
    strcat(s, "description: ");
    strcat(s, tmp->description);
    strcat(s, "\n");

    char* list = toString(tmp->otherAttributes);
    s = realloc(s, strlen(list) + strlen(s) + 1024);
    strcat(s, list);
    strcat(s, "\n");

    free(list);

    list = toString(tmp->rectangles);
    s = realloc(s, strlen(list) + strlen(s) + 1024);
    strcat(s, list);
    strcat(s, "\n");

    free(list);

    list = toString(tmp->circles);
    s = realloc(s, strlen(list) + strlen(s) + 1024);
    strcat(s, list);
    strcat(s, "\n");

    free(list);

    list = toString(tmp->paths);
    s = realloc(s, strlen(list) + strlen(s) + 1024);
    strcat(s, list);
    strcat(s, "\n");

    free(list);

    list = toString(tmp->groups);
    s = realloc(s, strlen(list) + 1000);
    strcat(s, list);
    strcat(s, "\n");
    
    free(list);
    
    return s;
}

// Function to delete image content and free all the memory.
void deleteSVGimage(SVGimage* img) {
    if (img == NULL){
	    return;
	}

    SVGimage* tmp = (SVGimage*)img;
    freeList(tmp->rectangles);
    freeList(tmp->circles);
    freeList(tmp->paths);
    freeList(tmp->groups);
    freeList(tmp->otherAttributes);
    free(tmp);
}


// Function that returns a list of all rectangles in the image.  
List* getRects(SVGimage* img) {
    if(img == NULL) {
        return NULL;
    }

    List * allrects = initializeList(rectangleToString, dummyDelete, compareRectangles);
    ListIterator iter = createIterator(img->rectangles);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Rectangle* r = (Rectangle*)elem;
        insertBack(allrects, r);
    }

    iter = createIterator(img->groups);
    while((elem = nextElement(&iter)) != NULL){
        rectanglesFromGroup(allrects, (Group*)elem);
    }

    return allrects;
}

// Function that returns a list of all circles in the image.  
List* getCircles(SVGimage* img) {
    if(img == NULL) {
        return NULL;
    }

    List * allcircles = initializeList(circleToString, dummyDelete, compareCircles);
    ListIterator iter = createIterator(img->circles);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Circle* c = (Circle*)elem;
        insertBack(allcircles, c);
    }

    iter = createIterator(img->groups);
    while((elem = nextElement(&iter)) != NULL){
        circlesFromGroup(allcircles, (Group*)elem);
    }

    return allcircles;
}

// Function that returns a list of all paths in the image.  
List* getPaths(SVGimage* img) {
    if(img == NULL) {
        return NULL;
    }

    List * allpaths = initializeList(pathToString, dummyDelete, comparePaths);
    ListIterator iter = createIterator(img->paths);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Path* p = (Path*)elem;
        insertBack(allpaths, p);
    }

    iter = createIterator(img->groups);
    while((elem = nextElement(&iter)) != NULL){
        pathsFromGroup(allpaths, (Group*)elem);
    }

    return allpaths;
}

// Function that returns a list of all groups in the image.  
List* getGroups(SVGimage* img) {
    if(img == NULL) {
        return NULL;
    }

    List * allgroups = initializeList(groupToString, dummyDelete, compareGroups);
    ListIterator iter = createIterator(img->groups);
    void* elem;

    while((elem = nextElement(&iter)) != NULL) {
        Group* g = (Group*)elem;
        insertBack(allgroups, g);
        groupsFromGroup(allgroups, g);
    }

    return allgroups;
}


// Function that returns the number of all rectangles with the specified area
int numRectsWithArea(SVGimage* img, float area) {
    int count = 0;

    if(img == NULL || area <= 0) {
        return count;
    }

    List * l = getRects(img);

    ListIterator iter = createIterator(l);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Rectangle* r = (Rectangle*)elem;
        float rectarea = ((r->height)*(r->width));
        
        if(ceil(rectarea) == ceil(area)) {
            count++; 
        }
    }

    freeList(l);
    return count;
}

// Function that returns the number of all circles with the specified area
int numCirclesWithArea(SVGimage* img, float area) {
    int count = 0;
    float pi = 3.14159265359;

    if(img == NULL || area <= 0) {
        return count;
    }

    List * l = getCircles(img);

    ListIterator iter = createIterator(l);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Circle* c = (Circle*)elem;
        int circlearea = ceil(pi*(c->r)*(c->r));
        
        if(circlearea == ceil(area)) {
            count++; 
        }
    }    

    freeList(l);
    return count;
}

// Function that returns the number of all paths with the specified data - i.e. Path.data field
int numPathsWithdata(SVGimage* img, char* data) {
    int count = 0;
    if(img == NULL || data == NULL || strcmp(data, "") == 0) {
        return count;
    }

    List * l = getPaths(img);
    ListIterator iter = createIterator(l);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Path* p = (Path*)elem;

        if(strcmp(data, p->data) == 0) {
            count++; 
        }
    }

    freeList(l);
    return count;
}

// Function that returns the number of all groups with the specified length - see A1 Module 2 for details
int numGroupsWithLen(SVGimage* img, int len){
    int count = 0;

    if(img == NULL || len < 0) {
        return count;
    }

    List * l = getGroups(img);

    ListIterator iter = createIterator(l);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Group* g = (Group*)elem;

        int totalelements = (((g->rectangles)->length) + ((g->circles)->length) + ((g->paths)->length) + ((g->groups)->length));

        if(totalelements == len) {
            count++; 
        }
    }    

    freeList(l);
    return count;
}


int numAttr(SVGimage* img) {
    int count = 0;

    if(img == NULL){
        return count;
    }

    count += ((img->otherAttributes)->length);

    //Go through rectangles and sum the length of each of their other attributes list
    void* elem;
    List * l = getRects(img);
    ListIterator iter = createIterator(l);

    while((elem = nextElement(&iter)) != NULL){
        Rectangle* r = (Rectangle*)elem;
        count += ((r->otherAttributes)->length);
    }
    freeList(l);


    //getCircles
    l = getCircles(img);
    iter = createIterator(l);

    while((elem = nextElement(&iter)) != NULL){
        Circle* c = (Circle*)elem;
        count += ((c->otherAttributes)->length);
    }
    freeList(l);


    //getPaths
    l = getPaths(img);
    iter = createIterator(l);

    while((elem = nextElement(&iter)) != NULL){
        Path* p = (Path*)elem;
        count += ((p->otherAttributes)->length);
    }
    freeList(l);

    //getGroups
    l = getGroups(img);
    iter = createIterator(l);

    while((elem = nextElement(&iter)) != NULL){
        Group* g = (Group*)elem;
        count += ((g->otherAttributes)->length);
    }
    freeList(l);


    return count;
}

//******************************A2 FUNCTIONS*******************************//
//******************************A2 FUNCTIONS*******************************//
//******************************A2 FUNCTIONS*******************************//

//check that tree is valid
SVGimage* createValidSVGimage(char* fileName, char* schemaFile) {
    if (fileName == NULL || schemaFile == NULL) {
        return NULL;
    }

    FILE *xmlfile;
    FILE *sfile;
    if ((xmlfile = fopen(fileName, "r")) == NULL) {
        return NULL;
    } else if ((sfile = fopen(schemaFile, "r")) == NULL) {
        fclose(xmlfile);
        return NULL;
    }
    fclose(xmlfile);
    fclose(sfile);

    
    //turn file into xmldoc pointer
    xmlDocPtr doc;
    char *XMLFileName = fileName;
    doc = xmlReadFile(XMLFileName, NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    //call function to validate xmldoc against schemefile
    bool isValid = validateXml(doc, schemaFile);

    if(isValid) {
        SVGimage * svg = createSVGimage(fileName);
        return svg;
    }

    return NULL;
}

//write an SVGimage object to file
bool writeSVGimage(SVGimage* doc, char* fileName) {
    if (doc == NULL || fileName == NULL) {
        return false;
    }

    bool validWrite = false;
    xmlDocPtr xmldoc = NULL;

    //call fxn to convert an svgimage object into an xmldoc struct
    xmldoc = svgToXml(doc);

    if(xmldoc == NULL) {
        return false;
    }

    int writeError = xmlSaveFormatFileEnc(fileName, xmldoc, "UTF-8", 1);

    //writeError will be -1 if xmlSaveFormatFileEnc encounters an error, if not the function wrote fine
    if(writeError != -1) {
        validWrite = true;
    }

    //free xml tree/doc
    xmlFreeDoc(xmldoc);
    xmlCleanupParser();

    return validWrite;
}

// take an svgimage struct and check it against a schemaFile and the requirments outlined in svgparser.h
bool validateSVGimage(SVGimage* image, char* schemaFile) {
    //is either input null 
    if(image == NULL || schemaFile == NULL) {
        return false;
    }

    //can we open the file
    FILE *sfile;
    if ((sfile = fopen(schemaFile, "r")) == NULL) {
        return false;
    }
    fclose(sfile);
    
    bool isValid = false;

    //turn the svgimage object into a xmldoc
    xmlDocPtr xmldoc = svgToXml(image);
    
    if(xmldoc == NULL) {
        return false;
    }

    //set isvalid to the bool indicating if the xml is valid
    isValid = validateXml(xmldoc, schemaFile);

    // if the xml is valid check if it's valid for svgparser.h's requirements
    if (isValid != 0) {
        isValid = checkSVG(image);
    }

    xmlFreeDoc(xmldoc);
    // xmlCleanupParser();

    return isValid;
}




void setAttribute(SVGimage* image, elementType elemType, int elemIndex, Attribute* newAttribute) {
    if(image == NULL || newAttribute == NULL) {
        return;
    }

    // check if the image we're adding to is valid and if the attribute is valid
    // (checkSVG(image) == 0) || 
    if((validateAttribute(newAttribute) == 0)) {
        return;
    }

    if(elemType == SVG_IMAGE){
        setSVGAttribute(image, newAttribute);

    } else if (elemType == RECT) {
        //check if index is out of bounds
        if(elemIndex >= getLength(image->rectangles)) {
            return;
        }

        //cycle through list of rectangles to get the one at the provided index
        ListIterator iter = createIterator(image->rectangles);
        void* elem; 
        int i = 0;
        while(i <= elemIndex) {
            i++;
            (elem = nextElement(&iter));
        }
        Rectangle* rectangle = (Rectangle*) elem;

        //call fxn to set the rectangle attribute sending correct rectangle
        setRectangleAttribute(rectangle, newAttribute);

    } else if (elemType == CIRC) {
        //check if index is out of bounds
        if(elemIndex >= getLength(image->circles)) {
            return;
        }

        //cycle through list of circles to get the one at the provided index
        ListIterator iter = createIterator(image->circles);
        void* elem; 
        int i = 0;
        while(i <= elemIndex) {
            i++;
            (elem = nextElement(&iter));
        }
        Circle* circle = (Circle*) elem;

        //call fxn to set the cirlce attribute sending correct circle
        setCircleAttribute(circle, newAttribute);
        
    } else if (elemType == PATH) {
        //check if index is out of bounds
        if(elemIndex >= getLength(image->paths)) {
            return;
        }

        //cycle through list of paths to get the one at the provided index
        ListIterator iter = createIterator(image->paths);
        void* elem; 
        int i = 0;
        while(i <= elemIndex) {
            i++;
            (elem = nextElement(&iter));
        }
        Path* path = (Path*) elem;

        //call fxn to set the path attribute sending correct circle
        setPathAttribute(path, newAttribute);

    } else if (elemType == GROUP) {
        //check if index is out of bounds
        if(elemIndex >= getLength(image->groups)) {
            return;
        }

        //cycle through list of groups to get the one at the provided index
        ListIterator iter = createIterator(image->groups);
        void* elem; 
        int i = 0;
        while(i <= elemIndex) {
            i++;
            (elem = nextElement(&iter));
        }
        Group* group = (Group*) elem;

        //call fxn to set the group attribute sending correct group
        setGroupAttribute(group, newAttribute);

    }

    
    return;
}


void addComponent(SVGimage* image, elementType type, void* newElement) {
    //check if any input is null
    if(image == NULL || newElement == NULL) {
        return;
    }

    //check if the image we're adding to is valid
    // if(checkSVG(image) == 0) {
    //     return;
    // }

    if (type == RECT) {
       Rectangle* newrect = (Rectangle*)newElement; 
       validateRectangle(newrect);
       insertBack(image->rectangles, newrect);

    } else if (type == CIRC) {
       Circle* newcircle = (Circle*)newElement; 
       validateCircle(newcircle);
       insertBack(image->circles, newcircle);
        
    } else if (type == PATH) {
       Path* newpath = (Path*)newElement; 
       validatePath(newpath);
       insertBack(image->paths, newpath);

    } 
}




char* attrToJSON(const Attribute *a) {
    Attribute* attribute = (Attribute*) a;

    if(a == NULL || validateAttribute(attribute) == 0) {
        char* rtn = calloc(24, sizeof(char)+4);
        strcpy(rtn, "{}");
        return rtn;
    }

    char* s = calloc((strlen(attribute->name) + strlen(attribute->value) + 128), sizeof(char)+16);
    strcat(s, "{\"name\":\"");
    strcat(s, attribute->name);
    strcat(s, "\",\"value\":\"");
    strcat(s, attribute->value);
    strcat(s, "\"}");

    return s;
}


char* circleToJSON(const Circle *c) {
    Circle* circle = (Circle*) c;

    if(c == NULL || validateCircle(circle) == 0) {
        char* rtn = calloc(24, sizeof(char)+4);
        strcpy(rtn, "{}");
        return rtn;
    }

    char buffer[32];
    char* s = calloc((strlen(circle->units) + 100), sizeof(char)+4);
    
    strcat(s, "{\"cx\":");
    sprintf(buffer, "%.2f", circle->cx);
    strcat(s, buffer);

    strcat(s, ",\"cy\":");
    sprintf(buffer, "%.2f", circle->cy);
    strcat(s, buffer);

    strcat(s, ",\"r\":");
    sprintf(buffer, "%.2f", circle->r);
    strcat(s, buffer);

    strcat(s, ",\"numAttr\":");
    sprintf(buffer, "%d", (circle->otherAttributes)->length);
    strcat(s, buffer);

    strcat(s, ",\"units\":\"");
    strcat(s, circle->units);
    strcat(s, "\"}");

    return s;
}

char* rectToJSON(const Rectangle *r) {
    return NULL;
}

char* pathToJSON(const Path *p) {
    return NULL;
}

char* groupToJSON(const Group *g) {
    return NULL;
}

char* attrListToJSON(const List *list) {
    return NULL;
}

char* circListToJSON(const List *list) {
    return NULL;
}

char* rectListToJSON(const List *list) {
    return NULL;
}

char* pathListToJSON(const List *list) {
    return NULL;
}

char* groupListToJSON(const List *list) {
    return NULL;
}

char* SVGtoJSON(const SVGimage* imge){
    return NULL;
}








//******************************A2 HELPER FUNCTIONS*******************************//
//******************************A2 HELPER FUNCTIONS*******************************//
//******************************A2 HELPER FUNCTIONS*******************************//




