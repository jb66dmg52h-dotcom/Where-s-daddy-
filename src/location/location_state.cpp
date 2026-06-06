#include "location/location_state.h"

#include "app_config.h"

namespace Location {

LocationState currentPlaceholderState() {
  return {
      false,
      false,
      true,
      AppConfig::PlaceholderSpeedKph,
      AppConfig::PlaceholderCity,
      AppConfig::PlaceholderUpdatedTime,
  };
}

}  // namespace Location
