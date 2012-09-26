<?php
/**
 * @file views-timeline.tpl.php
 * View template to output TimelineJS wrapper markup and include scripts
 */

global $language;
$json_source = '/_timelinejs/' . $view->name . '/' . $view->current_display;
if(is_array($view->args)) {
  $json_source .= '/' . implode('/', $view->args);
}
$settings = array(
  'width' => '100%',
  'height' => '500',
  'source' => $json_source,
  'embed_id' => $timelinejs_id,
  'lang' => $language->language,
);

// Include TimelineJS libraries
views_timelinejs_load_libraries();

// Include inline javascript
drupal_add_js(array('timelineJS' => $settings), 'setting');
drupal_add_js(drupal_get_path('module', 'views_timelinejs') . '/js/views_timelinejs.js');

?>
<div id="<?php print $timelinejs_id ?>" class="timelinejs">
</div>
