<?php
/**
 * @file
 * Long Text field integration as a tag source for TimelineJS.
 */

$plugin = array(
  'name' => t('Long Text field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'text_long',
  'callback' => 'views_timelinejs_text_long_tag',
);

function views_timelinejs_text_long_tag($value, $options = array()) {
  if (isset($value) && $value != "") {
    return $value['value'];
  }
  else {
    return FALSE;
  }
}
