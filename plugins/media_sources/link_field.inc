<?php
/**
 * @file
 * Link field integration as a media source for TimelineJS.
 */

$plugin = array(
  'name' => t('Twitter field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'link_field',
  'callback' => 'views_timelinejs_media_source_link_field_preparation',
);

function views_timelinejs_media_source_link_field_preparation($value, $options = array()) {
  return $value['url'];
}