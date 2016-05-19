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
  if ($library) {
    $width_unit = $vars['options']['timeline_theme']['width_unit'] ? '%' : '';
    $height_unit = $vars['options']['timeline_theme']['height_unit'] ? '%' : '';

    $width = check_plain($vars['options']['timeline_theme']['width']) . $width_unit;
    $height = check_plain($vars['options']['timeline_theme']['height']) . $height_unit;

    $settings = array(
      'options' => array(
        'width' => $width,
        'height' => $height,
        //'script_path' => base_path() . libraries_get_path('timeline') . '/compiled/',
      ),
      'source' => $vars['rows'],
      'embed_id' => $vars['timelinejs_id'],
      'processed' => FALSE,
    );

    if (empty($vars['options']['timeline_config']['language'])) {
      global $language;
      $settings['options']['language'] = $language->language;
    }
    else {
      $settings['options']['language'] = check_plain($vars['options']['timeline_config']['language']);
    }

    if ($vars['options']['timeline_config']['hash_bookmark']) {
      $settings['options']['hash_bookmark'] = TRUE;
    }

    if ($vars['options']['timeline_config']['start_at_end']) {
      $settings['options']['start_at_end'] = TRUE;
    }

    if ($vars['options']['timeline_config']['start_at_current']) {
      $settings['options']['start_at_end'] = FALSE;
      $settings['options']['start_at_slide'] = $vars['rows']['timeline']['start_at_current'];
    }

    if (isset($vars['options']['timeline_config']['scale_factor'])) {
      $settings['options']['scale_factor'] = check_plain($vars['options']['timeline_config']['scale_factor']);
    }

    // Add inline JavaScript.
    drupal_add_js(array('timelineJS' => array($settings)), 'setting');
    drupal_add_js(drupal_get_path('module', 'views_timelinejs') . '/js/views_timelinejs.js');
  }
  else {
    drupal_set_message(t('The TimelineJS library could not be loaded from the CDN.'), 'error', FALSE);
  }
}

/**
 * Add "read more" link after event body text.
 */
function theme_views_timelinejs_link_to_entity($vars) {
  return '<p class="read-more">' . l($vars['link_text'], $vars['uri']) . '</p>';
}
