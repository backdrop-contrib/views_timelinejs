<?php
/**
 * @file
 * Implementation of post_date (created, changed) as date source for TimelineJS.
 */
$plugin = array(
  'name' => t('Post Date'),
  'callback' => 'views_timelinejs_date_source_post_date_conversion',
  'handler_name' => 'views_handler_field_date',
  'field_type' => 'date',
);

/**
 * Converts different expected date formats to one global date format to be used in TimelineJS.
 * Respects Drupals TZ handling.
 *
 * @return
 *   date in defined output.
 *
 * Adds Z to ISODate to force TimelineJS to *not* use browser timezone.
 * Does not use field timezone. Uses drupals global tz instead.
 */
function views_timelinejs_date_source_post_date_conversion($date, $output_format, $options = array()) {
  $input_format = 'timestamp';
  $timezone = views_timelinejs_get_timezone();
  $db_timezone = 'UTC';
  switch ($output_format) {
    case 'iso8601':
      return views_timelinejs_convert_to_iso($date, $input_format, $timezone, $db_timezone);
    case 'gregorian':
      return views_timelinejs_convert_to_gregorian($date, $input_format, $timezone, $db_timezone);
    case 'timestamp':
      return views_timelinejs_convert_to_timestamp($date, $input_format, $timezone, $db_timezone);
  }
}
