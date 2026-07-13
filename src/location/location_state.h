#pragma once

struct LocationState {
  bool atHome;
  bool atWork;
  bool driving;
  int speedKph;
  const char *city;
  const char *updatedTime;
};

namespace Location {

LocationState currentPlaceholderState();

}  // namespace Location
