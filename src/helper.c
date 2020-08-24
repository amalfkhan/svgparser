/** 
 * Amal Khan 1033360
 * Assignment 2 CIS2750
 * Winter 2020
 * Prof. Denis Nikitenko
**/

//While iterator template taken from course content



#include <stdio.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

#define LIBXML_SCHEMAS_ENABLED



// Function to create a SVGimage object
SVGimage* createSVGStruct(char namespace[256], char title[256], char description[256]) {
    SVGimage* svg = calloc(1, sizeof(SVGimage)+10);
    
    // Copy in SVG namespace and truncate if needed
    if(namespace == NULL || (strcmp(namespace, "") == 0)) {
        strcpy(svg->namespace, "");

    } else if(strlen(namespace) > 255) {
        strncpy(svg->namespace, namespace, 255); 
        (svg->namespace)[255] = '\0';

    } else {
        strcpy(svg->namespace, namespace);
    }

    // Copy in SVG title and truncate if needed
    if(title == NULL || (strcmp(title, "") == 0)) {
        strcpy(svg->title, "");

    } else if(strlen(title) > 255) {
        strncpy(svg->title, title, 255); 
        (svg->title)[255] = '\0';

    } else {
        strcpy(svg->title, title);
    }

    // Copy in SVG description and truncate if needed
    if(description == NULL || (strcmp(description, "") == 0)) {
        strcpy(svg->description, "");

    } else if(strlen(description) > 255) {
        strncpy(svg->description, description, 255); 
        (svg->description)[255] = '\0';

    } else {
        strcpy(svg->description, description);
    }

    // Initialize empty lists for all elements
    svg->rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);
    svg->circles = initializeList(circleToString, deleteCircle, compareCircles);
    svg->paths = initializeList(pathToString, deletePath, comparePaths);
    svg->groups = initializeList(groupToString, deleteGroup, compareGroups);
    svg->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);

    return svg;
}



// Function to create an attribute object
Attribute* createAttribute(char* name, char* value) {
    Attribute* att = calloc(1, sizeof(Attribute)+10);
    
    // Copy in name and value and check for NULL

    if(name == NULL || (strcmp(name, "") == 0)) {
        att->name = calloc(16, sizeof(char)+10);
        strcpy(att->name, "");
    } else {
        att->name = calloc(strlen(name), sizeof(char)+10);
        strcpy(att->name, name);
    }

    if(value == NULL || (strcmp(value, "") == 0)) {
        att->value = calloc(16, sizeof(char)+10);
        strcpy(att->value, "");
    } else {
        att->value = calloc(strlen(value), sizeof(char)+10);
        strcpy(att->value, value);
    }
    
    return att;
}

// Function to clone an attribute object
Attribute* cloneAttribute(Attribute* att) {
    if(att == NULL) {
        return NULL;
    }

    Attribute* tmp = createAttribute(att->name, att->value);
    return tmp;
}



// Function to create a rectangle object
Rectangle* createRectangle(float x, float y, float width, float height, char units[50]) {
    Rectangle* rect = calloc(1, sizeof(Rectangle)+10);

    rect->x = x;
    rect->y = y;
    rect->width = width;
    rect->height = height;

    if(units == NULL) {
        strcpy(rect->units, "");
    }else {
        strcpy(rect->units, units);
    }
    
    // Initialize empty list for other attributes
    rect->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
    
    return rect;
}

// Function to clone a rectangle object
Rectangle* cloneRectangle(Rectangle* rectangle) {
    if(rectangle == NULL) {
        return NULL;
    }
    
    // Create a new rectangle with the provided rectangle's values
    Rectangle* tmp = createRectangle(rectangle->x, rectangle->y, rectangle->width, rectangle->height, rectangle->units);
    
    // Cycle through all of the attributes of the provided rectangle and clone/copy them to the new rectangle
    ListIterator iter = createIterator(rectangle->otherAttributes);
    void* elem;
    while((elem = nextElement(&iter)) != NULL){
        Rectangle* r = (Rectangle*)elem;
        insertBack(tmp->otherAttributes, cloneRectangle(r));
    }

    return tmp;
}



// Function to create a circle object
Circle* createCircle(float cx, float cy, float r, char units[50]) {
    Circle* circle = calloc(1, sizeof(Circle)+10);

    circle->cx = cx;
    circle->cy = cy;
    circle->r = r;

    if(units == NULL) {
        strcpy(circle->units, "");
    }else {
        strcpy(circle->units, units);
    }
    
    // Initialize an empty list to store other attributes
    circle->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);

    return circle;
}

// Function to clone a circle object
Circle* cloneCircle(Circle* circle) {
    if(circle == NULL) {
       return NULL;
    }
    
    // Create a new circle with the provided circle's values
    Circle* tmp = createCircle(circle->cx, circle->cy, circle->r, circle->units);
    
    // Cycle through all of the attributes of the provided circle and clone/copy them to the new circle
    ListIterator iter = createIterator(circle->otherAttributes);
    void* elem;
    while((elem = nextElement(&iter)) != NULL){
        Circle* c = (Circle*)elem;
        insertBack(tmp->otherAttributes, cloneCircle(c));
    }

    return tmp;
}



// Function to create a path object
Path* createPath(char* data) {
    Path* p = calloc(1, sizeof(Path)+10);
    
    // Copy data checking for NULL values
    if (data == NULL) {
        p->data = calloc(16, sizeof(char)+10);
        strcpy(p->data, "");

    } else {
        p->data = calloc(strlen(data)+4, sizeof(char)+10);
        strcpy(p->data, data);
    }

    // Initiazlize an empty list to store other attributes
    p->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);

    return p;
}

// Function to clone a path object
Path* clonePath(Path* path) {
    if(path == NULL) {
        return NULL;
    }

    // Create a new path with the provided path's values
    Path* tmp = createPath(path->data);
    ListIterator iter = createIterator(path->otherAttributes);
    void* elem;

    // Cycle through all of the attributes of the provided path and clone/copy them to the new path
    while((elem = nextElement(&iter)) != NULL){
        Attribute* a = (Attribute*)elem;
        insertBack(tmp->otherAttributes, cloneAttribute(a));
    }

    return tmp;
}



// Function to create a group object
Group* createGroup() {
    Group* grp = calloc(1, sizeof(Group)+10);
    
    // Initialize empty lists for all lists in a group
    grp->rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);
    grp->circles = initializeList(circleToString, deleteCircle, compareCircles);
    grp->paths = initializeList(pathToString, deletePath, comparePaths);
    grp->groups = initializeList(groupToString, deleteGroup, compareGroups);
    grp->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);

    return grp;
}

// Function to clone a group object
Group* cloneGroup(Group* group) {
    if(group == NULL) {
        return NULL;
    }

    Group* tmp = createGroup();
    
    // Recursively go through the provided group's lists of elements and clone/copy them to the new group 

    ListIterator iter = createIterator(group->rectangles);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Rectangle* r = (Rectangle*)elem;
        insertBack(tmp->rectangles, cloneRectangle(r));
    }

    iter = createIterator(group->circles);
    // void* elemc;
    while((elem = nextElement(&iter)) != NULL){
        Circle* c = (Circle*)elem;
        insertBack(tmp->circles, cloneCircle(c));
    }

    iter = createIterator(group->paths);
    // void* elemp;
    while((elem = nextElement(&iter)) != NULL){
        Path* p = (Path*)elem;
        insertBack(tmp->paths, clonePath(p));
    }

    iter = createIterator(group->groups);
    // void* elemg;
    while((elem = nextElement(&iter)) != NULL){
        Group* g = (Group*)elem;
        insertBack(tmp->groups, cloneGroup(g));
    }

    iter = createIterator(group->otherAttributes);
    // void* elema;
    while((elem = nextElement(&iter)) != NULL){
        Attribute* a = (Attribute*)elem;
        insertBack(tmp->otherAttributes, cloneAttribute(a));
    }

    return tmp;
}



// Function to parse a SVGFile and organize it contents
SVGimage* parseSVGFile(xmlNode * node, SVGimage * svg) {
    if(node == NULL || svg == NULL) {
        return NULL;
    }

    xmlNode *cur_node = node;

    for (cur_node = node; cur_node; cur_node = cur_node->next) { // Cycle through all nodes in a SVGimage

        if (cur_node->type == 1) {
            if ((strcmp((char*)cur_node->name,"svg") == 0)) { 
                
                // Copy in SVG namespace truncating if needed
                xmlNs * namespacestruct = cur_node->ns;
                if((char*)(namespacestruct->href) == NULL || (strcmp((char*)(namespacestruct->href), "") == 0)) {
                    return NULL;

                } else if(strlen((char*)(namespacestruct->href)) > 255) {
                    strncpy(svg->namespace, (char*)(namespacestruct->href), 255); 
                    (svg->namespace)[255] = '\0';

                } else {
                    strcpy(svg->namespace, (char*)(namespacestruct->href));
                }

                // Copy attributes associated with the SVG itself
                parseSVGNode(cur_node->properties, svg);

                // Recursive call to parse the rest of the file
                parseSVGFile(cur_node->children, svg);


            } else if ((strcmp((char*)cur_node->name,"title") == 0)) { 
                
                // Copy in title, truncate as needed
                if((char*)(cur_node->children->content) == NULL || (strcmp((char*)(cur_node->children->content), "") == 0)) {
                    strcpy(svg->title, "");

                } else if(strlen((char*)(cur_node->children->content)) > 255) {
                    strncpy(svg->title, (char*)(cur_node->children->content), 255); 
                    (svg->title)[255] = '\0';

                } else {
                    strcpy(svg->title, (char*)(cur_node->children->content));
                }
            
            } else if ((strcmp((char*)cur_node->name,"desc") == 0)) { //copy description
                // Copy in descrption, truncate as needed
                if((char*)(cur_node->children->content) == NULL || (strcmp((char*)(cur_node->children->content), "") == 0)) {
                    strcpy(svg->description, "");

                } else if(strlen((char*)(cur_node->children->content)) > 255) {
                    strncpy(svg->description, (char*)(cur_node->children->content), 255); 
                    (svg->description)[255] = '\0';

                } else {
                    strcpy(svg->description, (char*)(cur_node->children->content));
                }

            } else if (strcmp((char*)cur_node->name,"rect") == 0) { //copy any rectangles
                parseRectangle(cur_node->properties, svg->rectangles);

            } else if (strcmp((char*)cur_node->name,"circle") == 0) { //copy any circles
                parseCircle(cur_node->properties, svg->circles);

            } else if (strcmp((char*)cur_node->name,"path") == 0) { //copy any paths
                parsePath(cur_node->properties, svg->paths);

            }else if (strcmp((char*)cur_node->name,"g") == 0) {
                parseGroup(cur_node, svg->groups);
            }
        }
    }
    return svg;
}

// Function to parse a SVG node's properties
void parseSVGNode(xmlAttr * node, SVGimage * svg) {
    if(node == NULL || svg == NULL) {
        return;
    }

    xmlAttr *property = node;  

    // Cycle through all nodes in the SVG's properties
    // Copy the values into an attribute and insert them in the appropriate list  
    for(property = property; property != NULL; property = property->next) { 
        Attribute* attr = createAttribute((char*) (property->name), (char*)(property->children->content));
        insertBack(svg->otherAttributes, attr);
    }
}

// Function to parse a rectangle node's properties
void parseRectangle(xmlAttr *node, List* rectangles) {
    if(node == NULL || rectangles == NULL) {
        return;
    }

    xmlAttr *property = node;
    Rectangle* rect = createRectangle(0, 0, 0, 0, "");

    // Cycle through all nodes in the rectangle's properties
    // Copy the values into the appropriate attribute and add to struct or insert in list as needed
    for(property = property; property != NULL; property = property->next) {
        if(strcmp((char*) (property->name), "x") == 0) {
            char* units; 
            float xvalue = strtof((char*)(property->children->content), &units);
            rect->x = xvalue;

            if((units != NULL) && (strcmp(units, "") != 0)) {
                if(strlen(units) > 49) {
                    strncpy(rect->units, units, 49); 
                    (rect->units)[49] = '\0';
                } else {
                    strcpy(rect->units, units);
                }
            }

        } else if(strcmp((char*) (property->name), "y") == 0) {
            char* units; 
            float yvalue = strtof((char*)(property->children->content), &units);
            rect->y = yvalue;

            if((units != NULL) && (strcmp(units, "") != 0)) {
                if(strlen(units) > 49) {
                    strncpy(rect->units, units, 49); 
                    (rect->units)[49] = '\0';
                } else {
                    strcpy(rect->units, units);
                }
            }
            // rect->y = atof((char*)(property->children->content));

        } else if(strcmp((char*) (property->name), "width") == 0) {
            char* units; 
            float widthvalue = strtof((char*)(property->children->content), &units);
            rect->width = widthvalue;

            if((units != NULL) && (strcmp(units, "") != 0)) {
                if(strlen(units) > 49) {
                    strncpy(rect->units, units, 49); 
                    (rect->units)[49] = '\0';
                } else {
                    strcpy(rect->units, units);
                }
            }
            // rect->width = atof((char*)(property->children->content));

        } else if(strcmp((char*) (property->name), "height") == 0) {
            char* units; 
            float heightvalue = strtof((char*)(property->children->content), &units);
            rect->height = heightvalue;

            if((units != NULL) && (strcmp(units, "") != 0)) {
                if(strlen(units) > 49) {
                    strncpy(rect->units, units, 49); 
                    (rect->units)[49] = '\0';
                } else {
                    strcpy(rect->units, units);
                }
            }
            // rect->height = atof((char*)(property->children->content));

        } else {
            Attribute* attr = createAttribute((char*) (property->name), (char*)(property->children->content));
            insertBack(rect->otherAttributes, attr);
        }
    }

    insertBack(rectangles, rect);
}

// Function to parse a circle node's properties
void parseCircle(xmlAttr *node, List* circles) {
    if(node == NULL || circles == NULL) {
        return;
    }

    xmlAttr *property = node;
    Circle* circle = createCircle(0, 0, 0, "");

    // Cycle through all nodes in the circle's properties
    // Copy the values into the appropriate attribute and add to struct or insert in list as needed
    for(property = property; property != NULL; property = property->next) {
        if(strcmp((char*) (property->name), "cx") == 0) {
            char* units; 
            float cxvalue = strtof((char*)(property->children->content), &units);
            circle->cx = cxvalue;

            if((units != NULL) && (strcmp(units, "") != 0)) {
                if(strlen(units) > 49) {
                    strncpy(circle->units, units, 49); 
                    (circle->units)[49] = '\0';
                } else {
                    strcpy(circle->units, units);
                }
            }
            // circle->cx = atof((char*)(property->children->content));

        } else if(strcmp((char*) (property->name), "cy") == 0) {
            char* units; 
            float cyvalue = strtof((char*)(property->children->content), &units);
            circle->cy = cyvalue;

            if((units != NULL) && (strcmp(units, "") != 0)) {
                if(strlen(units) > 49) {
                    strncpy(circle->units, units, 49); 
                    (circle->units)[49] = '\0';
                } else {
                    strcpy(circle->units, units);
                }
            }
            // circle->cy = atof((char*)(property->children->content));

        } else if(strcmp((char*) (property->name), "r") == 0) {
            char* units; 
            float rvalue = strtof((char*)(property->children->content), &units);
            circle->r = rvalue;

            if((units != NULL) && (strcmp(units, "") != 0)) {
                if(strlen(units) > 49) {
                    strncpy(circle->units, units, 49); 
                    (circle->units)[49] = '\0';
                } else {
                    strcpy(circle->units, units);
                }
            }
            // circle->r = atof((char*)(property->children->content));

        } else {
            Attribute* attr = createAttribute((char*) (property->name), (char*)(property->children->content));
            insertBack(circle->otherAttributes, attr);
        }
    }

    insertBack(circles, circle);
}

// Function to parse a path-node's properties
void parsePath(xmlAttr *node, List* paths) {
    if(node == NULL || paths == NULL) {
        return;
    }

    xmlAttr *property = node;
    Path* path = createPath("");

    // Cycle through all nodes in the path's properties
    // Copy the values into the appropriate attribute and add to struct or insert in list as needed
    for(property = property; property != NULL; property = property->next) {
        if(strcmp((char*)(property->name), "d") == 0) {
            free(path->data);
            path->data = calloc(strlen((char*)(property->children->content))+4, sizeof(char)+10);
            strcpy(path->data, (char*)(property->children->content));
            
        } else {
            Attribute* attr = createAttribute((char*) (property->name), (char*)(property->children->content));
            insertBack(path->otherAttributes, attr);
        }

    }

    insertBack(paths, path);
}

// Function to parse a group node's properties
// Whatever element you're calling from passes the list of groups attached to it.
void parseGroup(xmlNode *node, List* list) { 
    if(node == NULL || list == NULL) {
        return;
    }
   
    xmlAttr* groupAttribute = node->properties;
    xmlNode* groupChildren = node->children;
    Group* g = createGroup();
    insertBack(list, g);

    // Copy a group's attribute's to its otherAttributes list
    for(groupAttribute = groupAttribute; groupAttribute != NULL; groupAttribute = groupAttribute->next) {
        Attribute* attr = createAttribute((char*) (groupAttribute->name), (char*)(groupAttribute->children->content));
        insertBack(g->otherAttributes, attr);
    }

    // Go through each a group's lists and call the element fuctions as needed to copy them into structs
    // Recursively call for groups
    for (groupChildren = groupChildren; groupChildren != NULL; groupChildren = groupChildren->next) {
        if(groupChildren->type == 1) {
            if (strcmp((char*)groupChildren->name,"rect") == 0) { //copy any rectangles
                parseRectangle(groupChildren->properties, g->rectangles);

            } else if (strcmp((char*)groupChildren->name,"circle") == 0) { //copy any circles
                parseCircle(groupChildren->properties, g->circles);

            } else if (strcmp((char*)groupChildren->name,"path") == 0) { //copy any paths
                parsePath(groupChildren->properties, g->paths);

            } else if(strcmp((char*)groupChildren->name,"g") == 0) { 
                parseGroup(groupChildren, g->groups);

            }
        }
    }

}



// Function to recursively get all rectangles in a group and its subgroups
void rectanglesFromGroup (List* l, Group* g) {
    ListIterator iter = createIterator(g->rectangles);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Rectangle* r = (Rectangle*)elem;
        insertBack(l, r);
    }

    if((g->groups)->length == 0) {
        return;
    } else {
        iter = createIterator(g->groups);

        while((elem = nextElement(&iter)) != NULL){
            rectanglesFromGroup(l, (Group*)elem);
        }
    }
}

// Function to recursively get all circles in a group and its subgroups
void circlesFromGroup (List* l, Group* g) {
    ListIterator iter = createIterator(g->circles);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Circle* c = (Circle*)elem;
        insertBack(l, c);
    }

    if((g->groups)->length == 0) {
        return;
    } else {
        iter = createIterator(g->groups);

        while((elem = nextElement(&iter)) != NULL){
            circlesFromGroup(l, (Group*)elem);
        }
    }
}

// Function to recursively get all paths in a group and its subgroups
void pathsFromGroup (List* l, Group* g) {
    ListIterator iter = createIterator(g->paths);
    void* elem;

    while((elem = nextElement(&iter)) != NULL){
        Path* p = (Path*)elem;
        insertBack(l, p);
    }

    if((g->groups)->length == 0) {
        return;
    } else {
        iter = createIterator(g->groups);

        while((elem = nextElement(&iter)) != NULL){
            pathsFromGroup(l, (Group*)elem);
        }
    }
}

// Function to recursively get all groups in a group and its subgroups
void groupsFromGroup (List* l, Group* g) {
    if((g->groups)->length == 0) {
        return;
    } else {
        ListIterator iter = createIterator(g->groups);
        void* elem;

        while((elem = nextElement(&iter)) != NULL){
            Group* g2 = (Group*)elem;
            insertBack(l, g2);
            groupsFromGroup(l, g2);
        }
    }

}



//Dummy delete function that does nothing
void dummyDelete(void *a) {
    return;
}


//******************************A2 HELPER FUNCTIONS*******************************//
//******************************A2 HELPER FUNCTIONS*******************************//
//******************************A2 HELPER FUNCTIONS*******************************//

// fuction to iterate through svg and validate
bool checkSVG(SVGimage* svgimage) {
    // bool isValid = false;

    if(svgimage == NULL) {
        return false;
    }

    // namespace mustnt be null
    if(svgimage->namespace == NULL) {
        return false;
    }

    // lists in svgimage mustnt be null
    if(svgimage->rectangles == NULL || svgimage->circles == NULL || svgimage->paths == NULL || svgimage->groups == NULL || svgimage->otherAttributes == NULL) {
        return false;
    }

    //call fxn to validate otherAttributes
    if (validateListOfOtherAttributes(svgimage->otherAttributes) == 0) {
        return false;
    }

    //call fxn to validate rectangles
    if (validateListOfRectangles(svgimage->rectangles) == 0) {
        return false;
    }

    //call fxn to validate circles
    if (validateListOfCircles(svgimage->circles) == 0) {
        return false;
    }

    //call fxn to validate paths
    if (validateListOfPaths(svgimage->paths) == 0) {
        return false;
    }

    //call fxn to validate groups
    if (validateListOfGroups(svgimage->groups) == 0) {
        return false;
    }
    
    return true;
}



// functions to validate a list of a given shape structs
bool validateListOfPaths (List* paths) {
    if(paths == NULL) {
        return false;
    }

    //go through each path and make sure that it's attributes are correct
    ListIterator iter = createIterator(paths);
    void* elem; 
    while((elem = nextElement(&iter)) != NULL) {
        Path* path = (Path*) elem;

        //call function that validates a given path
        if(validatePath(path) == 0) {
            return false;
        }
    }
    return true;
}

bool validateListOfCircles (List* circles) {
    if(circles == NULL) {
        return false;
    }

    //go through each circle and make sure that it's attributes are correct
    ListIterator iter = createIterator(circles);
    void* elem; 
    while((elem = nextElement(&iter)) != NULL) {
        Circle* circle = (Circle*) elem;
        if(validateCircle(circle) == 0) {
            return false;
        }
    }
    return true;
}

bool validateListOfRectangles (List* rectangles) {
    if(rectangles == NULL) {
        return false;
    }
    //go through each rectangle and make sure that it's attributes are correct
    ListIterator iter = createIterator(rectangles);
    void* elem; 
    while((elem = nextElement(&iter)) != NULL) {
        Rectangle* rectangle = (Rectangle*) elem;
        if(validateRectangle(rectangle) == 0) {
            return false;
        }
    }
    return true;
}

bool validateListOfGroups (List* groups) {
    if(groups == NULL) {
        return false;
    }

    //go through each group and make sure that it's lists and attributes are correct
    ListIterator iter = createIterator(groups);
    void* elem; 
    while((elem = nextElement(&iter)) != NULL) {
        Group* group = (Group*) elem;
        
        //check if the associated lists have been initialized
        if(group->rectangles == NULL || group->circles == NULL || group->paths == NULL || group->groups == NULL || group->otherAttributes == NULL) {
            return false;
        }

        //go through each group's rectangles to validate
        if (validateListOfRectangles(group->rectangles) == 0) {
            return false;
        }

        //go through each group's circles to validate
        if (validateListOfCircles(group->circles) == 0) {
            return false;
        }

        //go through each group's paths to validate
        if (validateListOfPaths(group->paths) == 0) {
            return false;
        }

        //go through each group's groups to validate
        if (validateListOfGroups(group->groups) == 0) {
            return false;
        }
        
        //go through each group's otherAttributes to validate
        if (validateListOfOtherAttributes(group->otherAttributes) == 0) {
            return false;
        }
    }
    
    return true;  
}

bool validateListOfOtherAttributes (List* otherAttributes) {
    if(otherAttributes == NULL) {
        return false;
    }

    //go through each attribute and make sure that it's correct
    ListIterator iter = createIterator(otherAttributes);
    void* elem; 
    while((elem = nextElement(&iter)) != NULL) {
        Attribute* attribute = (Attribute*) elem;
        if(validateAttribute(attribute) == 0) {
            return false;
        }

    }
    return true;
}



// functions to validate a single shape struct
bool validatePath (Path* path) {
    if(path == NULL) {
        return false;
    }

    //check if the otherAttributes list has been initialized
    if(path->otherAttributes == NULL) {
        return false;
    }

    //check if the path's data has been initialized
    if (path->data == NULL) {
        return false;
    }
    
    //go through each path's otherAttributes to validate
    if (validateListOfOtherAttributes(path->otherAttributes) == 0) {
        return false;
    }

    return true;
}

bool validateCircle (Circle* circle) {
    if(circle == NULL) {
        return false;
    }

    //check if the otherAttributes list has been initialized
    if(circle->otherAttributes == NULL) {
        return false;
    }

    //check if the radius is >= 0
    if (circle->r < 0) {
        return false;
    }
    
    //go through each circle's otherAttributes to validate
    if (validateListOfOtherAttributes(circle->otherAttributes) == 0) {
        return false;
    }
    return true;
}

bool validateRectangle (Rectangle* rectangle) {
    if(rectangle == NULL) {
        return false;
    }

    //check if the otherAttributes list has been initialized
    if(rectangle->otherAttributes == NULL) {
        return false;
    }

    //check if the width and height are >=0
    if (rectangle->width < 0 || rectangle->height < 0) {
        return false;
    }
    
    //go through each rectangle's otherAttributes to validate
    if (validateListOfOtherAttributes(rectangle->otherAttributes) == 0) {
        return false;
    }
    return true;
}

bool validateAttribute (Attribute* attribute) {
    if(attribute == NULL) {
        return false;
    }

    // check that the name and value have been initialized
    if (attribute->name == NULL || attribute->value == NULL) {
        return false;
    }
    return true;
}

bool validateGroup (Group* group) {
    if(group == NULL) {
        return false;
    }

    //check if the associated lists have been initialized
    if(group->rectangles == NULL || group->circles == NULL || group->paths == NULL || group->groups == NULL || group->otherAttributes == NULL) {
        return false;
    }

    //go through the group's otherAttributes to validate
    if (validateListOfOtherAttributes(group->otherAttributes) == 0) {
        return false;
    }

    return true;
}




//code heavily sourced from: http://knol2share.blogspot.com/2009/05/validate-xml-against-xsd-in-c.html
bool validateXml (xmlDocPtr xmldoc, char* schemaFile) {
    if (xmldoc == NULL || schemaFile == NULL) {
        return NULL;
    }

    FILE *sfile;
    if ((sfile = fopen(schemaFile, "r")) == NULL) {
        fclose(sfile);
        return NULL;
    }
    fclose(sfile);
    

    bool isValid = false;
    xmlDocPtr doc = xmldoc;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
    // char *XMLFileName = fileName;
    char *XSDFileName = schemaFile;

    xmlLineNumbersDefault(1);

    ctxt = xmlSchemaNewParserCtxt(XSDFileName);

    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);

    // doc = xmlReadFile(XMLFileName, NULL, 0);

    if (doc != NULL) {
        xmlSchemaValidCtxtPtr ctxt;
        int ret;
        ctxt = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
        ret = xmlSchemaValidateDoc(ctxt, doc);
        
        if (ret == 0) {
            isValid = true;
        }

        xmlSchemaFreeValidCtxt(ctxt);
        // xmlFreeDoc(doc);
    }

    // free the resource
    if(schema != NULL)
    xmlSchemaFree(schema);

    xmlSchemaCleanupTypes();
    xmlCleanupParser();
    xmlMemoryDump();

    return isValid;

}

//code heavily sourced from: http://xmlsoft.org/examples/tree2.c
xmlDocPtr svgToXml (SVGimage* doc) {
    if (doc == NULL) {
        return NULL;
    }

    SVGimage* svgdoc = doc;
    xmlDocPtr xmldoc = NULL;
    xmlNodePtr root_node = NULL;
    xmlNsPtr ns = NULL;

    LIBXML_TEST_VERSION;

    
    root_node = xmlNewNode(NULL, BAD_CAST "svg");
    
    // set namespace
    ns = xmlNewNs(root_node, (xmlChar*) svgdoc->namespace, NULL);
    xmlSetNs(root_node, ns);
    
    //check if title and description exist and add them if they do
    if((svgdoc->title != NULL) && (strcmp("",svgdoc->title) != 0)) {
        xmlNewChild(root_node, NULL, BAD_CAST "title", BAD_CAST svgdoc->title);
    }
    if((svgdoc->description != NULL) && strcmp("",svgdoc->description) != 0) {
        xmlNewChild(root_node, NULL, BAD_CAST "desc", BAD_CAST svgdoc->description);
    }


    //Add the other attributes of the svg from SVGdoc to xmldoc
    ListIterator iter = createIterator(svgdoc->otherAttributes);
    void* elem;
    while((elem = nextElement(&iter)) != NULL) {
        Attribute* tmpattr = (Attribute *) elem;
        xmlNewProp(root_node, BAD_CAST tmpattr->name, BAD_CAST tmpattr->value);
    }

    // TESTING: print all SVG properties from the xmldoc we created
    // for(xmlAttr* a = root_node->properties; a != NULL; a = a->next) {
    //     printf("NAME FROM NODE: %s\n", (char*)a->name);
    //     printf("VALUE FROM NODE: %s\n", (char*)a->children->content);
    // }

    //Add rectangles, circles, paths and groups from SVGdoc to xmldoc as children and their properties
    parseRectanglesWrite(root_node, svgdoc->rectangles);
    parseCirclesWrite(root_node, svgdoc->circles);
    parsePathsWrite(root_node, svgdoc->paths);
    parseGroupsWrite(root_node, svgdoc->groups);

    xmldoc = xmlNewDoc(BAD_CAST "1.0");
    xmlDocSetRootElement(xmldoc, root_node);

    return xmldoc;

}

//function to add groups to a xml tree node
void parseGroupsWrite (xmlNodePtr xmlnode, List* groups) {
    if(xmlnode == NULL || groups == NULL) {
        return;
    }
    
    //iterate through all the groups and all their lists
    ListIterator groupiter = createIterator(groups);
    void* elem;  
    while((elem = nextElement(&groupiter)) != NULL) {
        // printf("\n\nGROUP:\n");
        xmlNodePtr groupNode = NULL;
        Group* tmpgroup = (Group *) elem;

        if(tmpgroup->rectangles == NULL || tmpgroup->circles == NULL || tmpgroup->paths == NULL || tmpgroup->groups == NULL || tmpgroup->otherAttributes == NULL) {
            return;
        }

        //add a new group child node
        groupNode = xmlNewChild(xmlnode, NULL, BAD_CAST "g", NULL);  
        
        //iterate through the group's other attributes and add them as properties to the xml tree group node
        ListIterator iter = createIterator(tmpgroup->otherAttributes);
        void* elem2;
        while((elem2 = nextElement(&iter)) != NULL) {
            Attribute* tmpattr = (Attribute*) elem2;
            xmlNewProp(groupNode, BAD_CAST tmpattr->name, BAD_CAST tmpattr->value);
        }

        //call the function to iterate through the group's rectangles and add them as children to the xml tree group node
        parseRectanglesWrite(groupNode, tmpgroup->rectangles);
        parseCirclesWrite(groupNode, tmpgroup->circles);
        parsePathsWrite(groupNode, tmpgroup->paths);
        parseGroupsWrite(groupNode, tmpgroup->groups);

        // printf("\n\n\n\nGROUP ATTRIBUTES:\n");
        // for(xmlAttr* a = groupNode->properties; a != NULL; a = a->next) {
        //     printf("NAME FROM NODE: %s\n", (char*)a->name);
        //     printf("VALUE FROM NODE: %s\n", (char*)a->children->content);
        // }
    }
}

//function to add rectangles to xml tree
void parseRectanglesWrite (xmlNodePtr xmlnode, List* rectangles) {
    if(xmlnode == NULL || rectangles == NULL) {
        return;
    }

    //iterate through all of the rectangles list and add the attributes of each to the xml tree
    ListIterator rectiter = createIterator(rectangles);
    void* elem;  
    while((elem = nextElement(&rectiter)) != NULL) {
        // printf("\n\nRECTANGLE:\n");
        xmlNodePtr rectNode = NULL;
        Rectangle* tmprect = (Rectangle *) elem; // cast the current element to type rectangle
        char buf[256]; //buffer to store strings turned to floats
        
        if(tmprect->otherAttributes == NULL) {
            return;
        }

        //add a new rectangle child node
        rectNode = xmlNewChild(xmlnode, NULL, BAD_CAST "rect", NULL);     

        //turn x float into a string 
        sprintf(buf, "%f", tmprect->x);
        //add units if they exist
        if((tmprect->units != NULL) && (strcmp(tmprect->units, "") != 0)) {
            strcat(buf, tmprect->units);
        }
        //add x to the xmltree
        xmlNewProp(rectNode, BAD_CAST "x", BAD_CAST buf);
        
        //turn y float into a string 
        sprintf(buf, "%f", tmprect->y);
        //add units if they exist
        if((tmprect->units != NULL) && (strcmp(tmprect->units, "") != 0)) {
            strcat(buf, tmprect->units);
        }
        //add y to the xmltree
        xmlNewProp(rectNode, BAD_CAST "y", BAD_CAST buf);
        
        //float width to string
        sprintf(buf, "%f", tmprect->width);
        //add units if they exist
        if((tmprect->units != NULL) && (strcmp(tmprect->units, "") != 0)) {
            strcat(buf, tmprect->units);
        }
        //add width to the xmltree
        xmlNewProp(rectNode, BAD_CAST "width", BAD_CAST buf);
        
        //float height to string
        sprintf(buf, "%f", tmprect->height);
        //add units if they exist
        if((tmprect->units != NULL) && (strcmp(tmprect->units, "") != 0)) {
            strcat(buf, tmprect->units);
        }
        //add height to the xmltree
        xmlNewProp(rectNode, BAD_CAST "height", BAD_CAST buf);
        
        //iterate through a rectangles other attributes and add them to the xml tree
        ListIterator attriter = createIterator(tmprect->otherAttributes);
        void* elem2;
        while((elem2 = nextElement(&attriter)) != NULL) {
            Attribute* tmpattr = (Attribute*) elem2;
            xmlNewProp(rectNode, BAD_CAST tmpattr->name, BAD_CAST tmpattr->value);
        }

    // TESTING: print all rectangle properties from the xmldoc we created
    // for(xmlAttr* a = rectNode->properties; a != NULL; a = a->next) {
    //     printf("NAME FROM NODE: %s\n", (char*)a->name);
    //     printf("VALUE FROM NODE: %s\n", (char*)a->children->content);
    // }

    }
}

//function to add circles to xml tree
void parseCirclesWrite (xmlNodePtr xmlnode, List* circles) {
    if(xmlnode == NULL || circles == NULL) {
        return;
    }
    
    ListIterator circleiter = createIterator(circles);
    void* elem;

    while((elem = nextElement(&circleiter)) != NULL) {
        // printf("\n\nCIRCLE:\n");
        xmlNodePtr circleNode = NULL;
        Circle* tmpcircle = (Circle *) elem;
        char buf[256];

        if(tmpcircle->otherAttributes == NULL) {
            return;
        }

        //add a new rectangle child node
        circleNode = xmlNewChild(xmlnode, NULL, BAD_CAST "circle", NULL);

        //copy float cx to string
        sprintf(buf, "%f", tmpcircle->cx);
        //add units if they exist
        if((tmpcircle->units != NULL) && (strcmp(tmpcircle->units, "") != 0)) {
            strcat(buf, tmpcircle->units);
        }
        //add cx to the xmltree
        xmlNewProp(circleNode, BAD_CAST "cx", BAD_CAST buf);
        
        //float cy to string
        sprintf(buf, "%f", tmpcircle->cy);
        //add units if they exist
        if((tmpcircle->units != NULL) && (strcmp(tmpcircle->units, "") != 0)) {
            strcat(buf, tmpcircle->units);
        }
        //add cy to the xmltree
        xmlNewProp(circleNode, BAD_CAST "cy", BAD_CAST buf);
        
        //float r
        sprintf(buf, "%f", tmpcircle->r);
        //add units if they exist
        if((tmpcircle->units != NULL) && (strcmp(tmpcircle->units, "") != 0)) {
            strcat(buf, tmpcircle->units);
        }
        //add r to the xmltree
        xmlNewProp(circleNode, BAD_CAST "r", BAD_CAST buf);

        //copy attributes from otherAttributes list
        void* elem2;
        ListIterator attriter = createIterator(tmpcircle->otherAttributes);
        while((elem2 = nextElement(&attriter)) != NULL) {
            Attribute* tmpattr = (Attribute*) elem2;
            xmlNewProp(circleNode, BAD_CAST tmpattr->name, BAD_CAST tmpattr->value);
        }

        // TESTING: print all circle properties from the xmldoc we created
        // for(xmlAttr* a = circleNode->properties; a != NULL; a = a->next) {
        //     printf("NAME FROM NODE: %s\n", (char*)a->name);
        //     printf("VALUE FROM NODE: %s\n", (char*)a->children->content);
        // }

    }
}

//function to add paths to xml tree
void parsePathsWrite (xmlNodePtr xmlnode, List* paths) {
    if(xmlnode == NULL || paths == NULL) {
        return;
    }

    ListIterator pathiter = createIterator(paths);
    void* elem;
        
    while((elem = nextElement(&pathiter)) != NULL) {
        // printf("\n\nPATH:\n");
        Path* tmppath = (Path *) elem;
        
        if(tmppath->otherAttributes == NULL) {
            return;
        }

        xmlNodePtr pathNode = NULL;
        pathNode = xmlNewChild(xmlnode, NULL, BAD_CAST "path", NULL);

        //copy in path data
        xmlNewProp(pathNode, BAD_CAST "d", BAD_CAST tmppath->data);

        //copy in path's other attributes
        ListIterator attriter = createIterator(tmppath->otherAttributes);
        void* elem2;
        while((elem2 = nextElement(&attriter)) != NULL) {
            Attribute* tmpattr = (Attribute*) elem2;
            xmlNewProp(pathNode, BAD_CAST tmpattr->name, BAD_CAST tmpattr->value);
        }

        // TESTING: print all rectangle properties from the xmldoc we created
        // for(xmlAttr* a = pathNode->properties; a != NULL; a = a->next) {
        //     printf("NAME FROM NODE: %s\n", (char*)a->name);
        //     printf("VALUE FROM NODE: %s\n", (char*)a->children->content);
        // }

    }

}


//helpers to set the attributes of varying shape structures

void setRectangleAttribute (Rectangle* rectangle, Attribute* newAttribute) {
    if((validateRectangle(rectangle) == 0) || validateAttribute(newAttribute) == 0) {
        return;
    }
    //x, y, width, height? - string to float
    if(strcmp((char*) (newAttribute->name), "x") == 0) {
        rectangle->x = atof(newAttribute->value);
        deleteAttribute(newAttribute);
        return;
    } else if(strcmp((char*) (newAttribute->name), "y") == 0) {
        rectangle->y = atof(newAttribute->value);
        deleteAttribute(newAttribute);
        return;
    } else if(strcmp((char*) (newAttribute->name), "width") == 0) {
        rectangle->width = atof(newAttribute->value);
        deleteAttribute(newAttribute);
        return;
    } else if(strcmp((char*) (newAttribute->name), "height") == 0) {
        rectangle->height = atof(newAttribute->value);
        deleteAttribute(newAttribute);
        return;
    }

    //compare attribute to existing attributes
    if (checkExistingAttributes(rectangle->otherAttributes, newAttribute) == 1) {
        deleteAttribute(newAttribute);
        return;
    }

    // if the attribute isn't x, y, width, height or an existing one - add it to the back of the list
    insertBack(rectangle->otherAttributes, newAttribute);
}

void setCircleAttribute (Circle* circle, Attribute* newAttribute) {
    if(validateCircle(circle) == 0) {
        return;
    }

    //cx, cy, r? - string to float
    if(strcmp((char*) (newAttribute->name), "cx") == 0) {
        circle->cx = atof(newAttribute->value);
        deleteAttribute(newAttribute);
        return;
    } else if(strcmp((char*) (newAttribute->name), "cy") == 0) {
        circle->cy = atof(newAttribute->value);
        deleteAttribute(newAttribute);
        return;
    } else if(strcmp((char*) (newAttribute->name), "r") == 0) {
        circle->r = atof(newAttribute->value);
        deleteAttribute(newAttribute);
        return;
    }

    //compare attribute to existing attributes
    if (checkExistingAttributes(circle->otherAttributes, newAttribute) == 1) {
        deleteAttribute(newAttribute);
        return;
    }

    // if the attribute isn't cx, cy, r, or an existing one - add it to the back of the list
    insertBack(circle->otherAttributes, newAttribute);
}

void setPathAttribute (Path* path, Attribute* newAttribute) {
    if(validatePath(path) == 0) {
        return;
    }

    //d? - copy string
    if(strcmp((char*) (newAttribute->name), "d") == 0) {
        //free path data
        free(path->data);
        //allocate the right amount of space for the new data
        path->data = calloc(strlen((newAttribute->value))+4, sizeof(char)+16);
        //copy the new data value
        strcpy(path->data, newAttribute->value);
        //free the temporary new attribute holder
        deleteAttribute(newAttribute);
        return;
    }

    //compare attribute to existing attributes
    if (checkExistingAttributes(path->otherAttributes, newAttribute) == 1) {
        deleteAttribute(newAttribute);
        return;
    }

    // if the attribute isn't data or an existing one - add it to the back of the list
    insertBack(path->otherAttributes, newAttribute);
}

void setGroupAttribute (Group* group, Attribute* newAttribute) {
    // if(validateGroup(group) == 0) {
    //     return;
    // }

    //compare attribute to existing attributes
    if (checkExistingAttributes(group->otherAttributes, newAttribute) == 1) {
        deleteAttribute(newAttribute);
        return;
    }

    // if the attribute isn't an existing one - add it to the back of the list
    insertBack(group->otherAttributes, newAttribute);
}

void setSVGAttribute (SVGimage* img, Attribute* newAttribute) {
    // if(validateGroup(group) == 0) {
    //     return;
    // }

    //compare attribute to existing attributes
    if (checkExistingAttributes(img->otherAttributes, newAttribute) == 1) {
        deleteAttribute(newAttribute);
        return;
    }

    // if the attribute isn't an existing one - add it to the back of the list
    insertBack(img->otherAttributes, newAttribute);
}

bool checkExistingAttributes(List* list, Attribute* newAttribute) {
    ListIterator iter = createIterator(list);
    void* elem;
    while((elem = nextElement(&iter)) != NULL) {
        Attribute* currattribute = (Attribute*) elem;
        //check for NULLs before strcmp
        if((currattribute->name == NULL) || (newAttribute->name == NULL)) {
            return false;
        }

        //if there's a match delete current value, and copy in new value
        if(strcmp(currattribute->name, newAttribute->name) == 0) {
            
            //free current data at currattribute->name
            free(currattribute->value);
            //allocate the right amount of space at currattribute->value
            currattribute->value = calloc(strlen((newAttribute->value))+4, sizeof(char)+16);
            //copy the new attribute value
            strcpy(currattribute->value, newAttribute->value);
            //free the temporary new attribute holder
            return true;
        }
    }
    return false;
}