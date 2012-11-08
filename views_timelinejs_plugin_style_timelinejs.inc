<?php

/**
 * @file
 */

/**
 * This class holds all the funtionality used for the unformatted style plugin.
 */
class views_timelinejs_plugin_style_timelinejs extends views_plugin_style {

  /*
   * REMOVED OPTIONS_DEFINITION FOR NOW.
   *
  function option_definition() {
    // TODO: Define all plugin settings here
    $options = array(
      'timeline_fields' => array(
        'headline' => array('default' => '', 'translatable' => FALSE),
        'bodytext' => array('default' => '', 'translatable' => FALSE),
        'media' => array('default' => '', 'translatable' => FALSE),
        'date' => array('default' => '', 'translatable' => FALSE),
      ),
      'timeline_config' => array(
        'link_to_entity' => array('default' => '', 'translatable' => FALSE),
        'link_text_enabled' => array('default' => '', 'translatable' => FALSE),
        'link_text' => array('default' => '', 'translatable' => FALSE),
      ),
    );
    return array_merge(parent::option_definition(), $options);
  }
   */

  function options_form(&$form, &$form_state) {

    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#prefix' => '<div class="error messages">',
        '#markup' => t('You need at least one field before you can configure TimelineJS.'),
        '#suffix' => '</div>',
      );
      return;
    }

    $options = $this->display->handler->get_field_labels();
    $media_fields = array('0' => t('None'));
    $date_fields = array('0' => t('None'));
    $text_fields = array('0' => t('None'));

    // Load all date_source plugins.
    ctools_include('plugins');
    $date_sources = ctools_get_plugins('views_timelinejs', 'date_sources');
    $text_sources = ctools_get_plugins('views_timelinejs', 'text_sources');
    $media_sources = ctools_get_plugins('views_timelinejs', 'media_sources');

    // Go through all the field handlers to check support.
    foreach ($handlers as $field => $handler) {
      // Get a nice name for the field.
      $field_names[$field] = $handler->ui_name();
      if ($label = $handler->label()) {
        $field_names[$field] .= ' ("' . $label . '")';
      }

      if (isset($handler->definition['field_name'])) {
        $field_name = $handler->definition['field_name'];
        $field_info = field_info_field($field_name);
      }

      // Check if field is supported as a date source.
      foreach ($date_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if ($field_info['type'] == $source['field_type'] || $field == 'created' || $field == 'changed') {
            $date_fields[$field] = $field_names[$field];
          }
        }
      }

      // Check if field is a supported text source.
      foreach($text_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if ((isset($field_info['type']) && $field_info['type'] == $source['field_type']) || $field == 'title') {
            $text_fields[$field] = $field_names[$field];
          }
        }
      }

      // Check if field is a supported media source.
      foreach ($media_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if (isset($field_info['type']) && $field_info['type'] == $source['field_type']) {
            $media_fields[$field] = $field_names[$field];
          }
        }
      }
    }

    // TODO: Detect all field types, populate only compatible fields
    // Add default + supported fields to arrays.
    // Currently only checking support for date fields.
    $text_fields = $text_fields;
    $date_fields = $date_fields;
    $media_fields = $media_fields;

    $form['timeline_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('General configuration'),
      '#description' => t('Settings for how the Timeline will behave.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_config']['link_to_entity'] = array(
      '#type' => 'checkbox',
      '#title' => 'Link timeline items to entity',
      '#description' => t('If checked, headlines will be made links to entity.'),
      '#default_value' => isset($this->options['timeline_config']['link_to_entity']) ? $this->options['timeline_config']['link_to_entity'] : '',
    );
    $form['timeline_config']['link_text_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => 'Add a link to entity after bodytext',
      '#description' => t('Append a link to original entity to the end of the bodytext.'),
      '#default_value' => isset($this->options['timeline_config']['link_text_enabled']) ? $this->options['timeline_config']['link_text_enabled'] : '',
    );
    $form['timeline_config']['link_text'] = array(
      '#type' => 'textfield',
      '#title' => 'Link text',
      '#description' => t('Text that will be used in the link to entity'),
      '#default_value' => isset($this->options['timeline_config']['link_text']) ? $this->options['timeline_config']['link_text'] : 'Read more',
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[timeline_config][link_to_entity]"]' => array('value' => 1),
        ),
      ),
    );
    $form['timeline_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Field mappings'),
      '#description' => t('Select the fields to be used for different parts of the timeline.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_fields']['headline'] = array(
      '#type' => 'select',
      '#options' => $text_fields,
      '#title' => 'Select field for headline',
      '#description' => t('This field should be a text-like field'),
      '#default_value' => isset($this->options['timeline_fields']['headline']) ? $this->options['timeline_fields']['headline'] : '',
    );
    $form['timeline_fields']['bodytext'] = array(
      '#type' => 'select',
      '#options' => $text_fields,
      '#title' => 'Select field for bodytext',
      '#description' => t('This field should be a text-like field'),
      '#default_value' => isset($this->options['timeline_fields']['bodytext']) ? $this->options['timeline_fields']['bodytext'] : '',
    );
    $form['timeline_fields']['media'] = array(
      '#type' => 'select',
      '#options' => $media_fields,
      '#title' => 'Select field for media asset',
      '#description' => t('Only image fields are currently supported'),
      '#default_value' => isset($this->options['timeline_fields']['media']) ? $this->options['timeline_fields']['media'] : '',
    );
    $form['timeline_fields']['date'] = array(
      '#type' => 'select',
      '#options' => $date_fields,
      '#title' => 'Select field for date element',
      '#description' => t('Only UNIX timestamp-like date fields are currently supported (node created, updated, etc...)'),
      '#default_value' => isset($this->options['timeline_fields']['date']) ? $this->options['timeline_fields']['date'] : '',
    );
  }

  /**
   * Render the display in this style.
   */
  function render() {
    $view = $this->view;

    // We want to render some fields, because of field
    // rewriting and other field level processing
    $this->view->style_plugin->render_fields($this->view->result);

    $field_mapping = array(
      'startDate' => 'date',
      'endDate' => 'date',
      'headline' => 'headline',
      'text' => 'bodytext',
      'media' => 'media',
    );
    $link_text = isset($this->options['timeline_config']['link_text']) ? $this->options['timeline_config']['link_text'] : 'Read more';
    $rows = array();

    // TODO: Figure out how to detect field types and different rendering methods for them
    $media_field_type = isset($this->options['timeline_fields']['media']) ? $view->field[$this->options['timeline_fields']['media']]->field_info['type'] : NULL;

    // Build a TimelineJS friendly array from the views data
    foreach($this->view->result as $count => $row) {
      // Get the link to entity
      // TODO: Currently restricted to node views, should work with other entities also
      if ($this->options['timeline_config']['link_to_entity'] && $view->base_table == 'node' && isset($row->_field_data[$view->base_field]['entity'])) {
        $row->uri = entity_uri($row->_field_data[$view->base_field]['entity_type'], $row->_field_data[$view->base_field]['entity']);
        $row->link_to_entity = l(t(check_plain($link_text)), $row->uri['path']);
      }

      $fields = array();

      // Get basic data for each timeline entry field based on display handler settings
      foreach($field_mapping as $target_field => $source_field) {
        if(isset($this->options['timeline_fields'][$source_field])) {
          // Get field alias, so we can check agains $row if all fields have data
          $field_alias = $view->field[$this->options['timeline_fields'][$source_field]]->field_alias;
          if(isset($row->$field_alias)) {
            if(is_array($row->$field_alias) && !count($row->$field_alias)) {
              // The field data is propably empty, prevent from executing get_field_value()
            }
            else {
              // Get field's raw value
              $fields[$target_field] = $view->style_plugin->get_field_value($count, $this->options['timeline_fields'][$source_field]);
            }
          }
        }
      }

      // Apply additional field-level processing
      // TODO: Maybe it's not worth using general field mapping loop above,
      // since most of the fields require field-level processing
      if(isset($fields['startDate'])) {
        $fields['startDate'] = format_date($fields['startDate'], 'custom', 'Y,m,d');
      }
      if(isset($fields['endDate'])) {
        $fields['endDate'] = format_date($fields['endDate'], 'custom', 'Y,m,d');
      }
      if(isset($fields['media']) && is_array($fields['media'])) {
        $field_tmp = array_shift($fields['media']);
        if(isset($field_tmp['uri'])) {
          $fields['media'] = file_create_url($field_tmp['uri']);
        }
      }
      // We want to use rendered output for bodytext, because of
      // field level processing provided by views (trimming, etc)
      // Remove all markup, so that we don't get any broken HTML
      if(isset($fields['text'])) {
        $fields['text'] = strip_tags($this->view->style_plugin->rendered_fields[$count][$this->options['timeline_fields']['bodytext']]);
      }

      // Loop through fields if there are arrays and deassemble them to get value
      foreach($fields as $name => $field) {
        if(is_array($field)) {
          $field_tmp = array_shift($field);
          $fields[$name] = $field_tmp['value'];
        }

        // Sanitize all user inputted output
        $fields[$name] = check_plain($fields[$name]);
      }

      // Add links to original entity
      if(isset($fields['text']) && $this->options['timeline_config']['link_text_enabled']) {
        // Append link to entity in the end of bodytext
        $fields['text'] .= theme('views_timelinejs_link_to_entity', array('uri' => $row->uri['path'], 'link_text' => t($link_text)));
      }
      if(isset($fields['headline']) && isset($row->uri['path'])) {
        // Make headline a link to entity
        $fields['headline'] = l($fields['headline'], $row->uri['path']);
      }

      // Combine the results array with processed row data
      $rows[$count]['startDate'] = isset($fields['startDate']) ? $fields['startDate'] : '';
      $rows[$count]['endDate'] = isset($fields['endDate']) ? $fields['endDate'] : '';
      $rows[$count]['headline'] = isset($fields['headline']) ? $fields['headline'] : '';
      $rows[$count]['text'] = isset($fields['text']) ? $fields['text'] : '';
      $rows[$count]['asset']['media'] = isset($fields['media']) ? $fields['media'] : '';
    }

    // Let modules alter timeline data before rendering by implementing
    // hook_views_timelinejs_data_alter(&$rows, $view)
    drupal_alter('views_timelinejs_data', $rows, clone $view);

    // Prepare data array that TimelineJS understands
    $data = array(
      'timeline' => array(
        'headline' => 'Title',
        'type' => 'default',
        'date' => $rows,
      ),
    );

    // Skip rendering if view is being edited or previewed
    if(!$view->editing) {
      return theme('views_timelinejs', array('view' => $view, 'options' => $this->options, 'rows' => $data));
    }
    else {
      return '<pre>' . print_r($data, 1) . '</pre>';
      //return t('TimelineJS style does not support preview mode.');
    }
  }
}