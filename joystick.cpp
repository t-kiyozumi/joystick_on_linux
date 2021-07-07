#include <linux/joystick.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <iostream>

typedef struct
{
  uint16_t X;
  uint16_t Y;
  uint16_t A;
  uint16_t B;
  uint16_t LB;
  uint16_t LT;
  uint16_t RB;
  uint16_t RT;
  uint16_t start;
  uint16_t back;
  int16_t axes1_x;
  int16_t axes1_y;
  int16_t axes0_x;
  int16_t axes0_y;
} controler_state;

void write_controler_state(controler_state *controler, js_event event)
{
  switch (event.type)
  {
  case JS_EVENT_BUTTON:
    if (event.number == 1)
    {
      controler->A = event.value;
    }
    if (event.number == 2)
    {
      controler->B = event.value;
    }
    if (event.number == 0)
    {
      controler->X = event.value;
    }
    if (event.number == 3)
    {
      controler->Y = event.value;
    }
    if (event.number == 4)
    {
      controler->LB = event.value;
    }
    if (event.number == 5)
    {
      controler->RB = event.value;
    }
    if (event.number == 6)
    {
      controler->LT = event.value;
    }
    if (event.number == 7)
    {
      controler->RT = event.value;
    }
    if (event.number == 9)
    {
      controler->start = event.value;
    }
    if (event.number == 0)
    {
      controler->X = event.value;
    }
    if (event.number == 3)
    {
      controler->Y = event.value;
    }
    if (event.number == 8)
    {
      controler->back = event.value;
      // printf("bock %d", controler->back);
    }

    break;
  case JS_EVENT_AXIS:
    if (event.number == 0)
    {
      controler->axes0_x = event.value;
    }
    if (event.number == 1)
    {
      controler->axes0_y = -event.value;
    }
    if (event.number == 2)
    {
      controler->axes1_x = event.value;
    }
    if (event.number == 3)
    {
      controler->axes1_y = -event.value;
    }
    break;
  default:
    /* Ignore init events. */
    break;
  }
}

int main()
{
  // int fd = open("/dev/input/js0", O_NONBLOCK);
  int fd = open("/dev/input/js0", O_RDONLY);
  struct js_event event;
  controler_state *controler;
  controler = (controler_state *)malloc(sizeof(controler_state));

  while (1)
  {
    read(fd, &event, sizeof(event));
    write_controler_state(controler, event);
    printf("X0 = %d,Y0=%d\n",controler->axes0_x,controler->axes0_y);
    usleep(1000);
  }
}
