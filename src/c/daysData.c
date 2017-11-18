#include "daysData.h"

static int dayIndex = 0;
static void day_initialise(struct day* this, int numSteps, char* description, int steps[]) {
  this->numSteps = numSteps;
  this->steps = malloc(sizeof(struct day) * numSteps);
  this->description = description;
  for (int i = 0 ; i < numSteps ; i++) {
    this->steps[i] = (struct step) {.duration = steps[i], .isWalk = i % 2 == 1};
  }
  this->dayIndex = dayIndex;
  this->title = malloc(strlen("Week %d"));
  this->subtitle = malloc(strlen("Day %d"));
  snprintf(this->title, SIZE_OF_WEEK_STRING, "Week %d", (dayIndex / NUM_OF_DAYS_PER_WEEK) + 1);
  snprintf(this->subtitle, SIZE_OF_DAY_STRING, "Day %d", (dayIndex % NUM_OF_DAYS_PER_WEEK) + 1);
  dayIndex++;
}

static void setup_copy_week(struct day *days, int steps[], char *description, int numSteps, int week_number) {
  for(int i = 0 ; i < NUM_OF_DAYS_PER_WEEK ; i++) {
    int dayIndex = i + ((week_number - 1) * 3);
    day_initialise(&days[dayIndex], numSteps, description, steps); 
  }
}

// Week one
static void setup_week_one(struct day *days) {
  int steps[] = {600, 60, 600, 60, 600, 60, 600};
  char *description = "10m Run, 1m Walk x 4";
  setup_copy_week(days, steps, description, 7, 1);
}

// Week two
static void setup_week_two(struct day *days) {
  int steps[] = {900, 60, 900, 60, 900};
  char *description = "15m Run, 1m Walk x 3";
  setup_copy_week(days, steps, description, 5, 2);
}

// Week three
static void setup_week_three(struct day *days) {
  int steps[] = {1020, 60, 1020, 60, 1020};
  char *description = "17m Run, 1m Walk x 3";
  setup_copy_week(days, steps, description, 5, 3);
}

// Week four
static void setup_week_four(struct day *days) {
  int steps[] = {1080, 60, 1080, 60, 1080};
  char *description = "18m Run, 1m Walk x 3";
  setup_copy_week(days, steps, description, 5, 4);
}

// Week five
static void setup_week_five(struct day *days) {
  int day_one_steps[] = {1320,60,1320,};
  day_initialise(&days[12], 3, "22m Run, 1m Walk x 2", day_one_steps);
  int day_two_steps[] = {1500, 60, 1500};
  day_initialise(&days[13], 3, "25m Run, 1m Walk x 2", day_two_steps);
  int day_three_steps[] = {1800, 60, 1800};
  day_initialise(&days[14], 3, "30m Run, 1m Walk x 2.", day_three_steps);
}

// Week six
static void setup_week_six(struct day *days) {
  int steps[] = {3600};
  char *description = "60m Run";
  setup_copy_week(days, steps, description, 5, 6);
}

struct day* get_days_data() {
  struct day *days = malloc(sizeof(struct day) * NUM_TOTAL_DAYS);
  setup_week_one(days);
  setup_week_two(days);
  setup_week_three(days);
  setup_week_four(days);
  setup_week_five(days);
  setup_week_six(days);
  return days;
}

void freeDays(struct day *days) {
  for(int counter = 0 ; counter<NUM_TOTAL_DAYS ; counter++) {
    struct day target_day = days[counter];
    free(target_day.steps);
    free(target_day.title);
    free(target_day.subtitle);
  }
  free(days);
}