#include <stdio.h>
#include "LinkedListAPI.h"
#include "SVGParser.h"
#include "helper.h"

int attributeDebug = 0;
int toStringDebug = 0;
int cloneDebug = 0;
int createSVGImageDebug = 0;
int createSVGStructDebug = 0;
int createPathDebug = 0;
int getRectsManualDebug = 0;
int groupToStringDebug = 0;
int getRectsDebug = 0;
int getCirclesDebug = 0;
int getPathsDebug = 0;
int numRectsWithAreaDebug = 0;
int getGroupsDebug = 0;
int numGroupsWithLenDebug = 0;
int numCirclesWithAreaDebug = 0;
int numAttrDebug = 0;
int createValidSVGimageDebug = 0;
int writeSVGimageDebug = 0;
int validateSVGimageDebug = 0;
int addComponentDebug = 0;
int validateListOfPathsDebug = 0;
int setRectangleAttributeDebug = 0;
int attrToJSONDebug = 0;
int circleToJSONDebug = 1;


void attributeDebugTests ();
void toStringDebugTests ();
void cloneDebugTests ();
void createSVGImageDebugTests (char *argv);
void createSVGStructDebugTests ();
void createPathDebugTests ();
void getRectsManualDebugTests ();
void groupToStringDebugTests ();
void getRectsDebugTests (char *fileName);
void getCirclesDebugTests (char *fileName);
void getPathsDebugTests (char* fileName);
void numRectsWithAreaDebugTests (char* fileName);
void getGroupsDebugTests (char* fileName);
void numGroupsWithLenDebugTests (char* fileName);
void numCirclesWithAreaDebugTests (char* fileName);
void numAttrDebugTests (char* fileName);
void createValidSVGimageDebugTests (char* fileName, char* schemaFile);
void writeSVGimageDebugTests (char* doc, char* fileName);
void validateSVGimageDebugTests (char* fileName, char* schemaFile);
void addComponentDebugTests (char* fileName);
void validateListOfPathsDebugTests ();
void setRectangleAttributeDebugTests ();
void attrToJSONDebugTests();
void circleToJSONDebugTests();



int main(int argc, char **argv) {
   if(cloneDebug) {
      cloneDebugTests();
   }

   if(toStringDebug) {
      toStringDebugTests();
   }
   
   if(attributeDebug) {
      attributeDebugTests();
   }   

   if(createSVGImageDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      createSVGImageDebugTests(argv[1]);
   }

   if(createSVGStructDebug) {
      createSVGStructDebugTests();
   }

   if(createPathDebug) {
      createPathDebugTests();
   }

   if(getRectsManualDebug) {
      getRectsManualDebugTests();
   }

   if(groupToStringDebug) {
      groupToStringDebugTests();
   }
   
   if(getRectsDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      getRectsDebugTests(argv[1]);
   }

   if(getCirclesDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      getCirclesDebugTests(argv[1]);
   }

   if(getPathsDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      getPathsDebugTests(argv[1]);
   }

   if(numRectsWithAreaDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      numRectsWithAreaDebugTests(argv[1]);
   }

   if(getGroupsDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      getGroupsDebugTests(argv[1]);
   }

   if(numGroupsWithLenDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
     numGroupsWithLenDebugTests(argv[1]);
   }

   if(numCirclesWithAreaDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      numCirclesWithAreaDebugTests(argv[1]);
   }

   if(numAttrDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      numAttrDebugTests(argv[1]);
   }

   if(createValidSVGimageDebug) {
      if(argc < 3) {
         printf("Expected 2 args\n");
         return 0;
      }
      createValidSVGimageDebugTests(argv[1], argv[2]);
   }

   if(writeSVGimageDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      writeSVGimageDebugTests(argv[1], "testfile.svg");
   }

   if(validateSVGimageDebug) {
      if(argc < 3) {
         printf("Expected 2 args\n");
         return 0;
      }
      validateSVGimageDebugTests(argv[1], argv[2]);
   }

   if(addComponentDebug) {
      if(argc < 2) {
         printf("Expected 1 arg\n");
         return 0;
      }
      addComponentDebugTests(argv[1]);
   }

   if(validateListOfPathsDebug) {
      validateListOfPathsDebugTests ();
   }

   if(setRectangleAttributeDebug) {
      setRectangleAttributeDebugTests();
   }

   if(attrToJSONDebug) {
      attrToJSONDebugTests();
   }

   if(circleToJSONDebug) {
      circleToJSONDebugTests();
   }

   return 0;
}


void circleToJSONDebugTests() {
   //create a valid circle
   Circle* c = createCircle(1, 2, 3, "cm");

   //create an invalid circle - negetive r
   Circle* c2 = createCircle(1, 2, -3, "cm");

   
   //check attrToJSON's handeling of a valid circle
   char* s = circleToJSON(c);
   printf("%s\n", s);

   //check circleToJSON's handeling of NULL instead of a circle
   char* s2 = circleToJSON(NULL);
   printf("%s\n", s2);

   //check circleToJSON's handeling an invalid circle
   char* s3 = circleToJSON(c2);
   printf("%s\n", s3);
   
   //don't have to free s2 and s3 beacuse they should be string literals (no memory allocated when creating the strings)
   deleteCircle(c);
   deleteCircle(c2);
   free(s);
   free(s2);
   free(s3);

}

void attrToJSONDebugTests() {
   //create a valid attribute
   Attribute* a = createAttribute("Jesus", "Wheel");

   //create an invalid attribute - NULL name
   Attribute* a2 = createAttribute("Hello", "Come Again");
   free(a2->name);
   a2->name = NULL;
   
   //check attrToJSON's handeling of a valid attribute
   char* s = attrToJSON(a);
   printf("%s\n", s);

   //check attrToJSON's handeling of NULL instead of an attribute
   char* s2 = attrToJSON(NULL);
   printf("%s\n", s2);

   //check attrToJSON's handeling an invalid attribute
   char* s3 = attrToJSON(a2);
   printf("%s\n", s3);
   
   //don't have to free s2 and s3 beacuse they should be string literals (no memory allocated when creating the strings)
   deleteAttribute(a);
   deleteAttribute(a2);
   free(s);
   free(s2);
   free(s3);
}

void setRectangleAttributeDebugTests () {
   Rectangle* r1 = createRectangle(1.0, 1.0, 1.0, 1.0, "mm");
   // Rectangle* r2 = createRectangle(2.0, 2.0, 2.0, 2.0, "mm");
   // Rectangle* r3 = createRectangle(3.0, 3.0, 3.0, 3.0, "mm");
   // Rectangle* r4 = createRectangle(4.0, 4.0, 4.0, 4.0, "mm");
   // Rectangle* r5 = createRectangle(5.0, 5.0, 5.0, 5.0, "mm");

   char* hello = rectangleToString(r1);
   printf("%s\n", hello);
   free(hello);

   // List* rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);
   // insertBack(rectangles, r1);
   // insertBack(rectangles, r2);
   // insertBack(rectangles, r3);
   // insertBack(rectangles, r4);
   // insertBack(rectangles, r5);

   Attribute* atttmp = createAttribute("x", "2");
   Attribute* atttmp2 = createAttribute("fill", "yellow");

   setRectangleAttribute(r1, atttmp);
   setRectangleAttribute(r1, atttmp2);

   hello = rectangleToString(r1);
   printf("%s\n", hello);
   free(hello);

   deleteRectangle(r1);
   // deleteAttribute(atttmp);
   // deleteAttribute(atttmp2);


}

void validateListOfPathsDebugTests () {
   Path* validPath = createPath("This is a valid path\n");
   
   //create a path with a null otherAttributes list
   Path* nullOtherAttributes = createPath("some data");
   nullOtherAttributes->otherAttributes = NULL;

   //create a path with NULL data 
   Path* nullData = createPath("some data");
   nullData->data = NULL;

   List * paths = initializeList(pathToString, deletePath, comparePaths);

   insertBack(paths, validPath);
   insertBack(paths, nullData);
   insertBack(paths, nullOtherAttributes);

   printf("PASS/FAIL bool: %d\n", validateListOfPaths(paths));

}

void addComponentDebugTests(char* fileName) {
   SVGimage* img = createSVGimage(fileName);
   Rectangle* r1 = createRectangle(1.0, 1.0, 1.0, 1.0, "mm");
   addComponent(img, RECT, r1);
   deleteSVGimage(img);
}

void validateSVGimageDebugTests(char* fileName, char* schemaFile) {
   // SVGimage* img = createSVGimage(fileName);
   // bool isvalid = validateSVGimage(img, schemaFile);
   // printf("test 1\n");
   // if(isvalid) {
   //    printf("DOCUMENT VALID\n");
   // } else {
   //    printf("DOCUMENT INVALID\n");
   // }

   // deleteSVGimage(img);

   // printf("test 2\n");
   SVGimage* img = createSVGimage(fileName);
   Attribute* a = createAttribute(NULL, "NULL NAME");
   free(a->name);
   a->name = NULL;


   bool isvalid = validateAttribute (a);

   if(isvalid) {
      printf("ATTRIBUTE VALID\n");
   } else {
      printf("ATTRIBUTE INVALID\n");
   }


   // setAttribute(img, SVG_IMAGE, 0, a);
   insertBack(img->otherAttributes, a);
   // char* test = SVGimageToString(img);
   // printf("%s", test);
   isvalid = checkSVG(img);

   if(isvalid) {
      printf("DOCUMENT VALID\n");
   } else {
      printf("DOCUMENT INVALID\n");
   }
   // free(test);
   // deleteAttribute(a);
   deleteSVGimage(img);

}

void writeSVGimageDebugTests(char* doc, char* fileName){
   SVGimage* img = createSVGimage(doc);
   writeSVGimage(img, fileName);
   deleteSVGimage(img);
}

void createValidSVGimageDebugTests(char* fileName, char* schemaFile){
   SVGimage* svg = createValidSVGimage(fileName, schemaFile);
   if(svg != NULL) {
      char* hello = SVGimageToString(svg);
      printf("%s\n", hello);
      free(hello);
      deleteSVGimage(svg);
   }
}

void numAttrDebugTests(char* fileName){
   SVGimage* svg = createSVGimage(fileName);
   int i = numAttr(svg);
   printf("NUM ATTR: %d\n", i);
   deleteSVGimage(svg);
}

void numGroupsWithLenDebugTests(char* fileName){
   SVGimage* svg = createSVGimage(fileName);
   int i = numGroupsWithLen(svg, 2);
   printf("NUM GROUPS WITH LENGTH X: %d\n", i);
   deleteSVGimage(svg);
}

void getGroupsDebugTests(char* fileName){
   SVGimage* svg = createSVGimage(fileName);
   List * g = getGroups(svg);
   char* s = toString(g);
   
   printf("NUM GROUPS: %d\n", g->length);
   printf("%s\n", s);
   
   freeList(g);
   free(s);
   deleteSVGimage(svg); 
}

void numRectsWithAreaDebugTests(char* fileName) {
   SVGimage* svg = createSVGimage(fileName);
   int i = numRectsWithArea(svg, 8);
   printf("NUM RECTANGLES: %d\n", i);
   deleteSVGimage(svg);
}

void numCirclesWithAreaDebugTests(char* fileName) {
   SVGimage* svg = createSVGimage(fileName);
   int i = numCirclesWithArea(svg, 4);
   printf("NUM CIRCLES: %d\n", i);
   deleteSVGimage(svg);
}

void getPathsDebugTests(char* fileName) {
   SVGimage* svg = createSVGimage(fileName);
   List * p = getPaths(svg);
   // char* s = SVGimageToString(svg);
   // char* s = toString(p);

   printf("TOTAL PATHS: %d\n", p->length);
   // printf("%s\n", s);
   freeList(p);
   // free(s);
   deleteSVGimage(svg); 
}

void groupToStringDebugTests() {
   Rectangle* r1 = createRectangle(1.0, 1.0, 1.0, 1.0, "mm");
   Rectangle* r2 = createRectangle(2.0, 2.0, 2.0, 2.0, "mm");
   Rectangle* r3 = createRectangle(3.0, 3.0, 3.0, 3.0, "mm");
   Rectangle* r4 = createRectangle(4.0, 4.0, 4.0, 4.0, "mm");
   Rectangle* r5 = createRectangle(5.0, 5.0, 5.0, 5.0, "mm");

   Group* g1 = createGroup();
   Group* g2 = createGroup();
   Group* g3 = createGroup();
   Group* g4 = createGroup();
   Group* g5 = createGroup();

   SVGimage* svg = createSVGStruct("", "", "");

   insertBack(g1->rectangles, r2);
   insertBack(g2->rectangles, r3);
   insertBack(g2->rectangles, r4);
   insertBack(g5->rectangles, r5);

   insertBack(g2->groups, g3);
   insertBack(g2->groups, g4);
   insertBack(g3->groups, g5);

   insertBack(svg->groups, g1);
   insertBack(svg->groups, g2);

   insertBack(svg->rectangles, r1);

   char* s = groupToString(g2);

   printf("%s\n", s);
   free(s);
   deleteSVGimage(svg);
}

void getRectsManualDebugTests() {
   Rectangle* r1 = createRectangle(1.0, 1.0, 1.0, 1.0, "mm");
   Rectangle* r2 = createRectangle(2.0, 2.0, 2.0, 2.0, "mm");
   Rectangle* r3 = createRectangle(3.0, 3.0, 3.0, 3.0, "mm");
   Rectangle* r4 = createRectangle(4.0, 4.0, 4.0, 4.0, "mm");
   Rectangle* r5 = createRectangle(5.0, 5.0, 5.0, 5.0, "mm");

   Group* g1 = createGroup();
   Group* g2 = createGroup();
   Group* g3 = createGroup();
   Group* g4 = createGroup();
   Group* g5 = createGroup();

   SVGimage* svg = createSVGStruct("", "", "");

   insertBack(g1->rectangles, r2);
   insertBack(g2->rectangles, r3);
   insertBack(g2->rectangles, r4);
   insertBack(g5->rectangles, r5);

   insertBack(g2->groups, g3);
   insertBack(g2->groups, g4);
   insertBack(g3->groups, g5);

   insertBack(svg->groups, g1);
   insertBack(svg->groups, g2);

   insertBack(svg->rectangles, r1);

   // List * r = getRects(svg);
   char* s = SVGimageToString(svg);
   // char* s = toString(r);

   printf("%s\n", s);
   free(s);
   deleteSVGimage(svg);

}

void getRectsDebugTests(char *fileName) {
   SVGimage* svg = createSVGimage(fileName);
   List * r = getRects(svg);
   // char* s = SVGimageToString(svg);
   char* s = toString(r);

   printf("%s\n", s);
   freeList(r);
   free(s);
   deleteSVGimage(svg); 
}

void getCirclesDebugTests(char *fileName) {
   SVGimage* svg = createSVGimage(fileName);
   List * c = getCircles(svg);
   // char* s = SVGimageToString(svg);
   char* s = toString(c);

   printf("%s\n", s);
   freeList(c);
   free(s);
   deleteSVGimage(svg); 
}

void createPathDebugTests() {
   Path* p1 = createPath("");
   Path* p2 = createPath("some data");

   char* p1str = pathToString(p1);
   char* p2str = pathToString(p2);

   printf("EMPTY STRING: %s\n", p1str);
   printf("DATA STRING: %s\n", p2str);

   free (p1str);
   free (p2str);
   deletePath(p1);
   deletePath(p2);
}

void createSVGStructDebugTests() {
   SVGimage* svg = createSVGStruct("this is longer than we want", "this is longer than we want", "jack");
   // char* hello = SVGimageToString(svg);
   // free(hello);
   deleteSVGimage(svg);
}

void createSVGImageDebugTests(char *fileName) {
   SVGimage* svg = createSVGimage(fileName);
   char* hello = SVGimageToString(svg);
   printf("%s\n", hello);
   free(hello);
   deleteSVGimage(svg);
}

void cloneDebugTests() {
      Circle* c1 = createCircle(2.0, 2.0, 2.0, "mm");
      Circle* c2 = cloneCircle(c1);
      
      char* s = circleToString(c1);
      printf("%s\n*********\n\n", s);
      free(s);

      s = circleToString(c2);
      printf("%s\n*********\n\n", s);
      free(s);

      deleteCircle(c1);
      deleteCircle(c2);


      Rectangle* r1 = createRectangle(3.0, 4.0, 5.0, 6.0, "mm");
      Rectangle* r2 = cloneRectangle(r1);
      
      s = rectangleToString(r1);
      printf("%s\n*********\n\n", s);
      free(s);

      s = rectangleToString(r2);
      printf("%s\n*********\n\n", s);
      free(s);

      deleteRectangle(r1);
      deleteRectangle(r2);


      Group* g1 = createGroup();
      Group* g2 = cloneGroup(g1);
      
      s = groupToString(g1);
      printf("%s\n*********\n\n", s);
      free(s);

      s = groupToString(g2);
      printf("%s\n*********\n\n", s);
      free(s);

      deleteGroup(g1);
      deleteGroup(g2);
}

void toStringDebugTests() {
      Attribute* atttmp1 = createAttribute("a1", "a2");
      Attribute* atttmp2 = createAttribute("b1", "b2");
      Attribute* atttmp3 = createAttribute("c1", "c2");

      Rectangle* recttmp = createRectangle(2.0, 4.0, 3.0, 3.0, "mm");
      insertBack(recttmp->otherAttributes, atttmp1);
      insertBack(recttmp->otherAttributes, atttmp2);
      insertBack(recttmp->otherAttributes, atttmp3);

      Circle* circtmp = createCircle(2.0, 2.0, 1.0, "mm");
      insertBack(circtmp->otherAttributes, cloneAttribute(atttmp2));
      insertBack(circtmp->otherAttributes, cloneAttribute(atttmp3));
      insertBack(circtmp->otherAttributes, cloneAttribute(atttmp1));

      Path* pathtmp = createPath("hellowrld");
      insertBack(pathtmp->otherAttributes, cloneAttribute(atttmp3));
      insertBack(pathtmp->otherAttributes, cloneAttribute(atttmp2));
      insertBack(pathtmp->otherAttributes, cloneAttribute(atttmp1));

      char* s = rectangleToString(recttmp);
      printf("%s", s);
      free(s);

      s = circleToString(circtmp);
      printf("%s", s);
      free(s);
      
      s = pathToString(pathtmp);
      printf("%s", s);
      free(s);
   
      deleteRectangle(recttmp);
      deleteCircle(circtmp);
      deletePath(pathtmp);
}

void attributeDebugTests() {
      printf("\nCREATE ATTRIBUTE TEST\n");
      Attribute* atttmp = createAttribute("jack", "jill");
      printf("Attribute Name: %s\nAttribute Value: %s\n\n**********\n", atttmp->name, atttmp->value);

      printf("\nCREATE EMPTY ATTRIBUTE TEST\n");
      Attribute* atttmp1 = createAttribute("", "6mm");
      printf("Attribute Name: %s\nAttribute Value: %s\n\n**********\n", atttmp1->name, atttmp1->value);

      // printf("\nATTRIBUTE TO STRING TEST\n");
      // char* attstr = attributeToString(atttmp);
      // printf("%s\n**********\n", attstr);

      // printf("\nCOMPARE ATTRIBUTE TEST - SHOULD PASS\n");
      // Attribute* atttmp2 = createAttribute("jack", "jill");
      // int cmp = compareAttributes(atttmp, atttmp2);
      // printf("Attribute 1 Name: %s\nAttribute 1 Value: %s\n", atttmp->name, atttmp->value);
      // printf("Attribute 2 Name: %s\nAttribute 2 Value: %s\nCompare Value: %d\n\n**********\n", atttmp2->name, atttmp2->value, cmp);

      // printf("\nCOMPARE ATTRIBUTE TEST - SHOULD FAIL\n");
      // Attribute* atttmp3 = createAttribute("Jesus", "Jimena");
      // int cmp2 = compareAttributes(atttmp, atttmp3);
      // printf("Attribute 1 Name: %s\nAttribute 1 Value: %s\n", atttmp->name, atttmp->value);
      // printf("Attribute 3 Name: %s\nAttribute 3 Value: %s\nCompare Value: %d\n\n**********\n", atttmp3->name, atttmp3->value, cmp2);

      deleteAttribute(atttmp);
      deleteAttribute(atttmp1);
      // deleteAttribute(atttmp2);
      // deleteAttribute(atttmp3);
      // free(attstr);
}