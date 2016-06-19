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
  $vars['width'] = $vars['timeline_options']['width'];
  $vars['height'] = $vars['timeline_options']['height'];

  $library_name = variable_get('views_timelinejs_library', 'timeline_cdn');

  // Load required libraries and styles.
  $library = drupal_add_library('views_timelinejs', $library_name);

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
    $font_library = drupal_add_library('views_timelinejs', $library_name . '_' . $vars['timeline_font']);
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
