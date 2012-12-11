<?php
/**
 * @file
 * Date module integration as a date source for TimelineJS.
 */

$plugin = array(
  'name' => t('Date (ISO) field for TimelineJS'),
  'callback' => 'views_timelinejs_date_iso_source_date_field_conversion',
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
function views_timelinejs_date_iso_source_date_field_conversion($date, $output_format, $options = array()) {
  $input_format = $options['field']['date_format'];
  $tz_handling = $options['field']['tz_handling'];
  $timezone = date_get_timezone($tz_handling);
  $db_timezone = date_get_timezone_db($tz_handling);
  switch ($output_format) {
    case 'iso8601':
      $ret['value'] = views_timelinejs_convert_to_iso($date['value'], $input_format, $timezone, $db_timezone);
      if (isset($date['value2'])) {
        $ret['value2'] = views_timelinejs_convert_to_iso($date['value2'], $input_format, $timezone, $db_timezone);
      }
      return $ret;
    case 'gregorian':
      $ret['value'] = views_timelinejs_convert_to_gregorian($date['value'], $input_format, $timezone, $db_timezone);
      if (isset($date['value2'])) {
        $ret['value2'] = views_timelinejs_convert_to_gregorian($date['value2'], $input_format, $timezone, $db_timezone);
      }
      return $ret;
    case 'timestamp':
      $ret['value'] = views_timelinejs_convert_to_timestamp($date['value'], $input_format, $timezone, $db_timezone);
      if (isset($date['value2'])) {
        $ret['value2'] = views_timelinejs_convert_to_timestamp($date['value2'], $input_format, $timezone, $db_timezone);
      }
      return $ret;
  }
}
