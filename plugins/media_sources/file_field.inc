<?php
/**
 * @file
 * Image field integration as a media source for TimelineJS.
 */

$plugin = array(
  'name' => t('File field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'file',
  'callback' => 'views_timelinejs_media_source_file_field_preparation',
);

/**
 * A callback function for formatting the field data to a format TimelineJS understands.
 *
 * @param
 *   $value - The whole field value. (fid, alt, title, etc..)
 *   $options - The field_information array.
 */
function views_timelinejs_media_source_file_field_preparation($value, $options = array()) {
  if (is_array($value)) {
    return file_create_url($value['uri']);
  }
  else {
    return FALSE;
  }
}
