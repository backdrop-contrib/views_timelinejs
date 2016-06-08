<?php

/**
 * Converts date strings to TimelineJS3-compatible date arrays.
 */
class TimelineDate extends DateTime implements TimelineDateInterface {

  /**
   * The original date string that was passed to the constructor.
   */
  protected $date_string;

  public function __construct($date_string, DateTimeZone $timezone = NULL) {
    $this->date_string = $date_string;

    // Disallow empty date strings.  They will cause DateTime::__construct() to
    // return a date object with the current time.
    if (empty($date_string)) {
      throw new Exception('Empty date strings are not allowed.');
    }

    try {
      parent::__construct($date_string, $timezone);
    }
    catch (Exception $e) {
      // @todo Decouple this error message from Drupal.  It should probably be
      // moved to the plugin class.
      drupal_set_message(t('The date "@date" does not conform to a <a href="@php-manual">PHP supported date and time format</a>.', array('@date' => $date_string, '@php-manual' => 'http://php.net/manual/en/datetime.formats.php')), 'warning');
    }
  }

  /**
   * {@inheritdoc}
   */
  public function getTimelineDateArray() {
    // The TimelineJS documentation doesn't say anything specific about whether
    // leading zeros should be included in date parts, but the examples do not
    // include them.  Therefore, they are omitted here.
    $exploded_date = explode(',', $this->format('Y,n,j,g,i,s'));

    // Re-key the date array with the property names that TimelineJS expects.
    return array(
      'year' => $exploded_date[0],
      'month' => $exploded_date[1],
      'day' => $exploded_date[2],
      'hour' => $exploded_date[3],
      'minute' => $exploded_date[4],
      'second' => $exploded_date[5],
      'display_date' => $this->date_string,
    );
  }

}
