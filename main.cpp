#include <string.h>
#include <stdio.h>
#include <cstdlib>

#include <switch.h>
/*
draws a rectangle. 
x, y, width, height, framebuf, maxwidth
*/
void drawRect(u32 x, u32 y, u32 width, u32 height, u32* framebuf, u32 maxwidth);
void clearScreen(u32* framebuf, u32 maxwidth, u32 maxheight);
int main(int argc, char *argv[]) {
	gfxInitDefault();

	u32 width, height;
	u32* framebuf= (u32*) gfxGetFramebuffer((u32*)&width, (u32*)&height);
	
	//player positions
	u32 p1=height/2,p2=height/2;

	//score
	u32 p1score=0,p2score=0;

	//ball position
	u32 bx = width/2;
	u32 by = height/2;
	
	//ball momentum
	u32 bmx=-5;
	u32 bmy=1;


	// Main loop
	while(appletMainLoop()) {
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

		framebuf= (u32*) gfxGetFramebuffer((u32*)&width, (u32*)&height);
		clearScreen(framebuf, width, height);

		//player 1
		JoystickPosition p1joy;
		hidJoystickRead(&p1joy, CONTROLLER_P1_AUTO, JOYSTICK_LEFT);
        if(p1joy.dy>77) { //move up
        	if(p1-80<5) {
        		p1=80;
        	} else {
        		p1-=5;
        	}
        } else if(p1joy.dy<0) { //move down
        	if(p1+80>=height) {
        		p1=height-80;
        	} else {
        		p1+=5;
        	}
        } 
        drawRect(20, p1-75, 15, 150, framebuf, width);


		//player 2
        JoystickPosition p2joy;
        hidJoystickRead(&p2joy, CONTROLLER_PLAYER_2, JOYSTICK_LEFT);
        if(p2joy.dy>400) { //move up
        	if(p2-80<5) {
        		p2=80;
        	} else {
        		p2-=5;
        	}
        } else if(p2joy.dy<-400) { //move down
        	if(p2+80>=height) {
        		p2=height-80;
        	} else {
        		p2+=5;
        	}
        } 
		drawRect(width-40, p2-75, 15, 150, framebuf, width);

		//ball
        bx+=bmx;
        by+=bmy;
		if(bx<=5) {//p2 win
			bx=width/2;
			by=height/2;
			bmx=-bmx;
			p2score+=1;
		} else if(bx>=width) { //p1 win
			bx=width/2;
			by=height/2;
			bmx=-bmx;
			p1score+=1;
		}
		//collision
		if(by<5) {
			by=5;
			bmy=-bmy;
		} else if(by>=height-5) {
			by=height-5;
			bmy=-bmy;
		}
		if(bx<35 && bx>20) {
			if(by>p1-75 && by<p1+75) {
				bmx=-bmx;
				if(p1joy.dy>100) {
					if(bmy<5)
						bmy-=1;
				} else if(p1joy.dy<-100) {
					if(bmy<5)
						bmy+=1;
				}
				bx=35;
				if(by==0)
					by=1;
			}
		}
		if(bx>width-55 && bx<width-20) {
			if(by>p2-75 && by<p2+75) {
				if(p2joy.dy>100) {
					bmy-=1;
				} else if(p2joy.dy<-100) {
					bmy+=1;
				}
				bmx=-bmx;
				bx=width-55;
			}
		}
		drawRect(bx-5, by-5, 10, 10, framebuf, width);


		//score
		switch(p1score) {//ugg
			case 0:
			drawRect(width/2-100, height-100, 10, 50, framebuf, width);
			drawRect(width/2-70, height-100, 10, 50, framebuf, width);
			drawRect(width/2-90, height-100, 30, 10, framebuf, width);
			drawRect(width/2-90, height-60, 30, 10, framebuf, width);
			break;
			case 1:
			drawRect(width/2-80, height-100, 10, 50, framebuf, width);
			break;
			case 2:
			drawRect(width/2-100, height-100, 30, 10, framebuf, width);
			drawRect(width/2-100, height-80, 30, 10, framebuf, width);
			drawRect(width/2-100, height-60, 30, 10, framebuf, width);

			drawRect(width/2-80, height-90, 10, 10, framebuf, width);
			drawRect(width/2-100, height-70, 10, 10, framebuf, width);
			break;
			case 3:
			drawRect(width/2-100, height-100, 30, 10, framebuf, width);
			drawRect(width/2-100, height-80, 30, 10, framebuf, width);
			drawRect(width/2-100, height-60, 30, 10, framebuf, width);

			drawRect(width/2-80, height-90, 10, 10, framebuf, width);
			drawRect(width/2-80, height-70, 10, 10, framebuf, width);
			break;
			case 4:
			drawRect(width/2-100, height-100, 10, 20, framebuf, width);
			drawRect(width/2-100, height-80, 20, 10, framebuf, width);

			drawRect(width/2-80, height-100, 10, 50, framebuf, width);
			break;
		}
		drawRect(width/2-10, height-80, 20, 10, framebuf, width);
		switch(p2score) {//ugg
			case 0:
			drawRect(width/2+100, height-100, 10, 50, framebuf, width);
			drawRect(width/2+70, height-100, 10, 50, framebuf, width);
			drawRect(width/2+80, height-100, 30, 10, framebuf, width);
			drawRect(width/2+80, height-60, 30, 10, framebuf, width);
			break;
			case 1:
			drawRect(width/2+80, height-100, 10, 50, framebuf, width);
			break;
			case 2:
			drawRect(width/2+80, height-100, 30, 10, framebuf, width);
			drawRect(width/2+80, height-80, 30, 10, framebuf, width);
			drawRect(width/2+80, height-60, 30, 10, framebuf, width);

			drawRect(width/2+100, height-90, 10, 10, framebuf, width);
			drawRect(width/2+80, height-70, 10, 10, framebuf, width);
			break;
			case 3:
			drawRect(width/2+80, height-100, 30, 10, framebuf, width);
			drawRect(width/2+80, height-80, 30, 10, framebuf, width);
			drawRect(width/2+80, height-60, 30, 10, framebuf, width);

			drawRect(width/2+100, height-90, 10, 10, framebuf, width);
			drawRect(width/2+100, height-70, 10, 10, framebuf, width);
			break;
			case 4:
			drawRect(width/2+80, height-100, 10, 20, framebuf, width);
			drawRect(width/2+80, height-80, 20, 10, framebuf, width);

			drawRect(width/2+100, height-100, 10, 50, framebuf, width);
			break;
		}
		if(p2score>4 || p1score>4) 
			break;



	gfxFlushBuffers();
	gfxSwapBuffers();
	gfxWaitForVsync();
}


gfxExit();
return 0;
}
void drawRect(u32 x, u32 y, u32 width, u32 height, u32* framebuf, u32 maxwidth) {
	u32 pos;
	u32 actualx = x+width;
	u32 actualy = y+height;
	u32 curX;
	while(y<actualy) {
		y++;
		for(curX=x; curX<actualx; curX++){
			pos = y * maxwidth + curX;
			framebuf[pos] = RGBA8_MAXALPHA(255,255,255);
		}
	}
}
void clearScreen(u32* framebuf, u32 maxwidth, u32 maxheight) {
	for(u32 y =0; y<maxheight; y++) {
		for(u32 x=0; x<maxwidth; x++){
			u32 pos = y * maxwidth + x;
			framebuf[pos] = RGBA8_MAXALPHA(0,0,0);
		}
	}
}
