<?php

/**
 * Preprocess function for views-timelinejs.tpl.php
 */
function template_preprocess_views_timelinejs(&$vars) {
  $view = $vars['view'];
  $vars['timelinejs_id'] = 'timelinejs_' . $view->name . '_' . $view->current_display;
}
