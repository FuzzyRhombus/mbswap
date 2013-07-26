//
//    switchMainDisplay.c
//
//    Now known as mbswap.
//
//    Copyright © 2012, 2013 Ryan Mastrolia.
//
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <IOKit/graphics/IOGraphicsLib.h>
#include <ApplicationServices/ApplicationServices.h>
#include <getopt.h>


#define MAX_DISPLAYS 16


CGDirectDisplayID * getDisplays(CGDisplayCount *count, CGDisplayCount *main, const bool verbose) {
    CGDisplayErr error;
    CGDisplayCount displayCount, i;
    CGDirectDisplayID mainDisplay, *displays;
    
    displays = malloc(MAX_DISPLAYS*sizeof(CGDirectDisplayID));
    
    mainDisplay = CGMainDisplayID();
    
    error = CGGetActiveDisplayList(MAX_DISPLAYS, displays, &displayCount);
    if (error != kCGErrorSuccess) {
        fprintf(stderr, "CGGetOnlineDisplayList: error %d.\n", error);
        free(displays);
        
        return 0;
    }
    
    for (i=0;i<displayCount;i++) {
        if (displays[i] == mainDisplay) *main = i;
    }
    
    *count = displayCount;
    
    if (verbose)
        printf("%i display(s) detected. Main is currently number %i in the list.\n", displayCount, *main);
    
    return displays;   
    
}

void setMainDisplay(CGDirectDisplayID* displays, CGDisplayCount displayCount, CGDisplayCount mainIndex, CGDisplayCount targetIndex, const bool verbose)
{
    int	dx, dy;
    CGDisplayCount i;
    
    CGDirectDisplayID  mainDisplay, targetDisplay, id;
	CGDisplayConfigRef config;

    mainDisplay = displays[mainIndex];
    targetDisplay = displays[targetIndex];
    
    if (mainDisplay != targetDisplay) {
    
        dx = -CGRectGetMinX(CGDisplayBounds(targetDisplay));
        dy = -CGRectGetMinY(CGDisplayBounds(targetDisplay));

        CGBeginDisplayConfiguration(&config);
        
        for (i=0;i<displayCount;i++) {
            id = displays[i];
        
            CGConfigureDisplayOrigin (config, id, CGRectGetMinX(CGDisplayBounds(id)) + dx, CGRectGetMinY(CGDisplayBounds(id)) + dy);
        }

        CGCompleteDisplayConfiguration (config, kCGConfigureForSession);
   
        if (verbose)
            printf("Changed main display from %i to %i\n", mainDisplay, targetDisplay);
        
    }

}
   
int main(int argc, char **argv) {
    
    CGDirectDisplayID* displays;
    CGDisplayCount count, mainIndex;
    
    int i;
    bool verbose = false, cyclic = false;
    
    // Get options if any
    while ((i = getopt(argc, argv, "vc")) != -1) {
        if (i == 'v') verbose = true;
        else if (i == 'c') cyclic = true;
    }
    
    // Get all active displays, and which one is currently the main display.
    displays = getDisplays(&count, &mainIndex, verbose);
    
    if (displays != 0 && count != 0) {
        if (cyclic) {
            
            if (verbose) printf("Using cyclic mode...\n");
            if (count >= 2) {
                int next = mainIndex+1;
                if (next >= count) mainIndex = 0;
                
                setMainDisplay(displays, count, mainIndex, next, verbose);
            
            } else {
                // If got to here, only one display found.
                fprintf(stderr, "Only 1 display detected, nothing to swap.\n");
            }
            
        } else {
            if (count == 2) {
    
                setMainDisplay(displays, 2, mainIndex, !mainIndex, verbose);
            
            } else {
                // need more than 1, less than 3
                fprintf(stderr, "This program toggles the main display between 2 displays. You must have more than one display connected, but no more than 2. If you have more than 2, use -c to cycle through displays.\n");
            }
        
        }
        
        free(displays);
        
    } else {
        
        // error getting displays
        fprintf(stderr, "Could not detect any displays.\n");
        return 1;
    }
    
    return 0;

}

