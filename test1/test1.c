#include <stdio.h>
#include <allegro.h>
#include <math.h>

int main() 
{
	int i = 10;
	float x, y, angle;
	MIDI *music;	
	
	printf("test int size = %d", sizeof(i));
	
	allegro_init();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_keyboard();
	// install_timer();
   
   /* Detect mouse presence */
   if (install_mouse() < 0) {
      textout_centre_ex(screen, font, "No mouse detected, but you need one!",
			SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0),
			makecol(255, 255, 255));
      readkey();
      return 0;
   }
   
	set_color_depth(8);
	set_gfx_mode(GFX_AUTODETECT, 320, 240, 0, 0);
	set_palette(desktop_palette);
	
	music = load_midi("ow.midi");
	play_midi(music, TRUE);
	
	BITMAP *buffer = create_bitmap(320, 240);
	PALETTE palette;
	BITMAP *mario = load_bitmap("battle1.bmp", palette);
	set_palette(palette);
	
	clear(buffer);
	
	while (!key[KEY_ESC])
	{
		poll_mouse();
		
		x = 50 * cos(angle);
		y = 50 * sin(angle);
		angle += 0.2;
		
		draw_sprite(buffer, mario, (int) (160 + x), (int) (100 + y));

		//prints yellow "Hello World!!!" in middle of screen
		textout_centre(buffer, font, "Hello World!!!", 160, 100, makecol(255, 255, 0));

		vsync();
		draw_sprite(screen, buffer, 0, 0);
		
				
		// rest(16);
		clear(buffer);
	}
	
	fade_out(2);
	
	destroy_bitmap(buffer);
	destroy_bitmap(mario);
	allegro_exit();
	return 0;
}