<?php
/**
 * @file
 * Text field integration as a tag source for TimelineJS.
 */

$plugin = array(
  'name' => t('Text field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'text',
  'callback' => 'views_timelinejs_text_tag',
);

function views_timelinejs_text_tag($value, $options = array()) {
  if (isset($value) && $value != "") {
    return $value['value'];
  }
  else {
    return FALSE;
  }
}
