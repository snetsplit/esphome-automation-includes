void set_climate() {
    if (id(auto_mode)) {
     ESP_LOGW("climate_temp", "applying mode: %f %f", id(${node_id}_my_climate).target_temperature, id(${node_id}_room_temperature).state);
     ClimateMode climateMode = id(${node_id}_my_climate).mode;
     ClimatePreset climatePreset = id(${node_id}_my_climate).preset.value();

     if(id(${node_id}_room_temperature).state < id(${node_id}_my_climate).target_temperature - $heat_on_below_set_temp) {
       climateMode = ClimateMode::CLIMATE_MODE_HEAT;
       ESP_LOGW("climate_mode", "Mode: [%s]", "heat");
     } else if(id(${node_id}_room_temperature).state  > id(${node_id}_my_climate).target_temperature + $cool_on_above_set_temp) {
       climateMode = ClimateMode::CLIMATE_MODE_COOL;
       ESP_LOGW("climate_mode", "Mode: [%s]", "cool");
     } 

     if((id(${node_id}_room_temperature).state < id(${node_id}_my_climate).target_temperature - $heat_turbo_on_below_set_temp) && (climateMode == ClimateMode::CLIMATE_MODE_HEAT)) {
       climatePreset = ClimatePreset::CLIMATE_PRESET_BOOST;
       ESP_LOGW("climate_preset", "Preset: [%s]", "boost");
     } else if((id(${node_id}_room_temperature).state > id(${node_id}_my_climate).target_temperature + $cool_turbo_on_above_set_temp) && (climateMode == ClimateMode::CLIMATE_MODE_COOL)) {
       climatePreset = ClimatePreset::CLIMATE_PRESET_BOOST;
       ESP_LOGW("climate_preset", "Preset: [%s]", "boost");
     } else if((id(${node_id}_room_temperature).state > id(${node_id}_my_climate).target_temperature + $heat_turbo_off_above_set_temp) && (climateMode == ClimateMode::CLIMATE_MODE_HEAT)) {
       climatePreset = ClimatePreset::CLIMATE_PRESET_NONE;
       ESP_LOGW("climate_preset", "Preset: [%s]", "boost");
     } else if((id(${node_id}_room_temperature).state < id(${node_id}_my_climate).target_temperature - $cool_turbo_off_below_set_temp) && (climateMode == ClimateMode::CLIMATE_MODE_COOL)) {
       climatePreset = ClimatePreset::CLIMATE_PRESET_NONE;
       ESP_LOGW("climate_preset", "Preset: [%s]", "boost");
     }  


     ESP_LOGW("climate_mode", "applying mode: %d %d", static_cast<int>(climateMode), static_cast<int>(id(${node_id}_my_climate).mode));
     if (climateMode != id(${node_id}_my_climate).mode) {
       ESP_LOGW("climate_mode", "applying mode: [%s]", "");
       auto call = id(${node_id}_my_climate).make_call();
       call.set_mode(climateMode);
       call.perform();
     }    

     ESP_LOGW("climate_preset", "applying preset: %d %d", static_cast<int>(climatePreset), static_cast<int>(id(${node_id}_my_climate).preset.value()));
     if (static_cast<int>(climatePreset) != static_cast<int>(id(${node_id}_my_climate).preset.value())) {
       ESP_LOGW("climate_preset", "applying preset: [%s]", "");
      auto call = id(${node_id}_my_climate).make_call();
      call.set_preset(climatePreset);
      call.perform();
     }
  }
}
