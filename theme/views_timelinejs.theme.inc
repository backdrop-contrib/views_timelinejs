<?php
/**
 * @file
 * Theme preprocessors.
 */

/**
 * Prepares variables for the TimelineJS style template.
 */
function template_preprocess_views_timelinejs(&$vars) {
  $library_location = config_get('views_timelinejs.settings', 'views_timelinejs_library');
  $view = $vars['view'];

  $id = backdrop_html_id('timelinejs_' . $view->name . '_' . $view->current_display);
  $style = 'width: ' . $vars['timeline_options']['width'] . '; height: ' .  $vars['timeline_options']['height'] . ';';
  $vars['div_attributes'] = backdrop_attributes(array('id' => $id, 'style' => $style, 'class' => 'timelinejs'));

  // Load required libraries and styles.
  $library = backdrop_add_library('views_timelinejs', 'timelinejs.' . $library_location);

  // Add inline JavaScript.
  $settings = array(
    'options' => _sanitize_timeline_options($vars['timeline_options']),
    'source' => $vars['rows'],
    'embed_id' => $id,
    'processed' => FALSE,
  );
  backdrop_add_js(array('timelineJS' => array($settings)), 'setting');
  backdrop_add_js(backdrop_get_path('module', 'views_timelinejs') . '/js/views_timelinejs.js');

  // Add alternate font CSS.
  if ($vars['timeline_font']) {
    $font_library = backdrop_add_library('views_timelinejs', 'timelinejs.' . $vars['timeline_font'] . '.' . $library_location);
  }
}

/**
 * Sanitizes the timeline options.
 */
function _sanitize_timeline_options($options) {
  // Sanitize the options.
  $options = array_map('check_plain', $options);
  // Remove empty values from the options before returning.
  return array_filter($options);
}
