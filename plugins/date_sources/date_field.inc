<?php
/**
 * @file
 * Date module integration as a date source for TimelineJS.
 */

$plugin = array(
  'name' => t('Date field for TimelineJS'),
  'callback' => 'views_timelinejs_date_source_date_field_conversion',
  'handler_name' => 'views_handler_field_field',
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
function views_timelinejs_date_source_date_field_conversion($date, $output_format, $options = array()) {
  $input_format = $options['field']['date_format'];
  $tz_handling = $options['field']['tz_handling'];
  $timezone = date_get_timezone($tz_handling);
  $db_timezone = dateget_timezone_db($tz_handling);
  switch ($output_format) {
    case 'iso8601':
      return views_timeline_convert_to_iso($date, $input_format, $timezone, $db_timezone);
    case 'gregorian':
      return views_timeline_convert_to_gregorian($date, $input_format, $timezone, $db_timezone);
    case 'timestamp':
      return views_timeline_convert_to_timestamp($date, $input_format, $timezone, $db_timezone);
  }
}
