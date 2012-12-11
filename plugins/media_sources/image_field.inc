<?php
/**
 * @file
 * Image field integration as a media source for TimelineJS.
 */

$plugin = array(
  'name' => t('Image field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'image',
  'callback' => 'views_timelinejs_media_source_image_field_preparation',
);

/**
 * A callback function for formatting the field data to a format TimelineJS understands.
 *
 * @param
 *   $value - The whole field value. (fid, alt, title, etc..)
 *   $options - The field_information array.
 */
function views_timelinejs_media_source_image_field_preparation($value, $options = array()) {
  if (is_array($value) && isset($value['uri'])) {
    return file_create_url($value['uri']);
  }
  else {
    return FALSE;
  }
}
