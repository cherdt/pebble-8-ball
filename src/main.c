#include <pebble.h>

Window *my_window;
TextLayer *text_layer;
void *cb_data;

char* get_response() {
  char* response[20];
  response[0] = "Signs Point To Yes";
  response[1] = "Yes";
  response[2] = "You May Rely On It";
  response[3] = "Ask Again Later";
  response[4] = "Concentrate And Ask Again";
  response[5] = "Outlook Good";
  response[6] = "My Sources Say No";
  response[7] = "Better Not Tell You Now";
  response[8] = "Without A Doubt";
  response[9] = "Reply Hazy Try Again";
  response[10] = "It Is Decidedly So";
  response[11] = "Cannot Predict Now";
  response[12] = "My Reply Is No";
  response[13] = "As I See It Yes";
  response[14] = "It Is Certain";
  response[15] = "Yes Definitely";
  response[16] = "Don't Count On It";
  response[17] = "Most Likely";
  response[18] = "Very Doubtful";
  response[19] = "Outlook Not So Good";
  return response[rand() % 20];
}

void display_prompt() {
  text_layer_set_text(text_layer, "Shake it up!");
}

void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  // Process tap on ACCEL_AXIS_X, ACCEL_AXIS_Y or ACCEL_AXIS_Z
  // Direction is 1 or -1
	text_layer_set_text(text_layer, get_response());
  app_timer_register(2000, display_prompt, cb_data);
}

void handle_init(void) {
    accel_tap_service_subscribe(&accel_tap_handler);
	  my_window = window_create();

	  text_layer = text_layer_create(GRect(0, 0, 144, 154));
	  // Set the text, font, and text alignment
	  text_layer_set_text(text_layer, "Shake it up!");
    display_prompt();
	  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

	  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer));

	  // Push the window
	  window_stack_push(my_window, true);

}

void handle_deinit(void) {
    accel_tap_service_unsubscribe();
    text_layer_destroy(text_layer);
	  window_destroy(my_window);
}

int main(void) {
    srand(time(0));
	  handle_init();
	  app_event_loop();
	  handle_deinit();
}
