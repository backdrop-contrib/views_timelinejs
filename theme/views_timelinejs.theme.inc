<?php
/**
 * @file
 * Theme preprocessors.
 */

/**
 * Preprocessor for views template.
 */
function template_preprocess_views_timelinejs(&$vars) {
  $view = $vars['view'];
  $vars['timelinejs_id'] = drupal_html_id('timelinejs_' . $view->name . '_' . $view->current_display);

  // Load required libraries and styles.
  $library = drupal_add_library('views_timelinejs', 'timelinejs_cdn');
  if ($library === FALSE) {
    watchdog('views_timelinejs', 'The TimelineJS library could not be loaded from the CDN.', NULL, WATCHDOG_ERROR);
    drupal_set_message(t('The timeline could not be loaded.  Refresh the page to try again.'), 'error', FALSE);
    return;
  }

  // Add inline JavaScript.
  $settings = array(
    'options' => sanitize_timeline_options($vars['timeline_options']),
    'source' => $vars['rows'],
    'embed_id' => $vars['timelinejs_id'],
    'processed' => FALSE,
  );
  drupal_add_js(array('timelineJS' => array($settings)), 'setting');
  drupal_add_js(drupal_get_path('module', 'views_timelinejs') . '/js/views_timelinejs.js');

  // Add alternate font CSS.
  if ($vars['timeline_font']) {
    $font_library = drupal_add_library('views_timelinejs', 'timelinejs_cdn_' . $vars['timeline_font']);
    if ($font_library === FALSE) {
      watchdog('views_timelinejs', 'The TimelineJS font library could not be loaded from the CDN.', NULL, WATCHDOG_ERROR);
      return;
    }
  }
}

/**
 * Sanitizes the timeline options.
 */
function sanitize_timeline_options($options) {
  // Sanitize the options.
  $options = array_map('check_plain', $options);
  // Remove empty values from the options before returning.
  return array_filter($options);
}
