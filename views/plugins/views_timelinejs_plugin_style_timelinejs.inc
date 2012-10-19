<?php

/**
 * @file
 */

/**
 * This class holds all the funtionality used for the unformatted style plugin.
 */
class views_timelinejs_plugin_style_timelinejs extends views_plugin_style {

  function option_definition() {
    // TODO: Define all plugin settings here
    $options = array(
      'timeline_fields' => array(
        'headline' => array('default' => '', 'translatable' => FALSE),
        'bodytext' => array('default' => '', 'translatable' => FALSE),
        'media' => array('default' => '', 'translatable' => FALSE),
        'date' => array('default' => '', 'translatable' => FALSE),
        'caption' => array('default' => '', 'translatable' => FALSE),
        'credit' => array('default' => '', 'translatable' => FALSE),
        'thumbnail' => array('default' => '', 'translatable' => FALSE),
        'era' => array('default' => '', 'translatable' => FALSE),
        'tag' => array('default' => '', 'translatable' => FALSE),
      ),
      'timeline_config' => array(
        'link_to_entity' => array('default' => '', 'translatable' => FALSE),
        'link_text_enabled' => array('default' => '', 'translatable' => FALSE),
        'link_text' => array('default' => '', 'translatable' => FALSE),
      ),
    );
    return array_merge(parent::option_definition(), $options);
  }

  function options_form(&$form, &$form_state) {
    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least one field before you can configure TimelineJS.') . '</div>',
      );
      return;
    }

    $options = $this->display->handler->get_field_labels();
    $fields = array('0' => t('None'));

    foreach($this->display->handler->get_option('fields') as $field) {
      $fields[$field['id']] = $options[$field['id']];
    }

    // TODO: Detect field types, populate only compatible fields
    $text_fields = $fields;
    $date_fields = $fields;
    $media_fields = $fields;
    $bool_fields = $fields;

    $form['timeline_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('General configuration'),
    );
    $form['timeline_config']['headline'] = array(
      '#type' => 'textfield',
      '#title' => 'Headline of Timeline JS',
      '#description' => t('If checked, headlines will be made links to entity.'),
      '#default_value' => isset($this->options['timeline_config']['headline']) ? $this->options['timeline_config']['headline'] : '',
    );
    $form['timeline_config']['width'] = array(
      '#type' => 'textfield',
      '#title' => 'Width of the timeline',
      '#description' => t('The width of the timeline.'),
      '#default_value' => isset($this->options['timeline_config']['width']) ? $this->options['timeline_config']['width'] : '100%',
    );
    $form['timeline_config']['height'] = array(
      '#type' => 'textfield',
      '#title' => 'Height of the timeline',
      '#description' => t('The height, in pixel of the timeline.'),
      '#default_value' => isset($this->options['timeline_config']['height']) ? $this->options['timeline_config']['height'] : '500',
    );
    $form['timeline_config']['start_zoom_adjust'] = array(
      '#type' => 'textfield',
      '#title' => 'Start zoom',
      '#description' => t('This will tweak the default zoom level. Equivalent to pressing the zoom in or zoom out button the specified number of times. Negative numbers zoom out. default is 0'),
      '#default_value' => isset($this->options['timeline_config']['start_zoom_adjust']) ? $this->options['timeline_config']['start_zoom_adjust'] : '0',
    );
    $form['timeline_config']['start_at_slide'] = array(
      '#type' => 'textfield',
      '#title' => 'Start slide',
      '#description' => t('You can tell TimelineJS to start at a specific slide number default is 0'),
      '#default_value' => isset($this->options['timeline_config']['start_at_slide']) ? $this->options['timeline_config']['start_at_slide'] : '0',
    );
    $form['timeline_config']['start_at_end'] = array(
      '#type' => 'select',
      '#options' => array('1'=>'yes', '0'=>'No'),
      '#title' => 'Start at the end ?',
      '#description' => t('Set to yes to start the timeline on the last date. Default is no'),
      '#default_value' => isset($this->options['timeline_config']['start_at_end']) ? $this->options['timeline_config']['start_at_end'] : '0',
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
    $form['timeline_fields']['caption'] = array(
      '#type' => 'select',
      '#options' => $text_fields,
      '#title' => 'Select field for media caption',
      '#description' => t('This field should be a text-like field'),
      '#default_value' => isset($this->options['timeline_fields']['caption']) ? $this->options['timeline_fields']['caption'] : '',
    );
    $form['timeline_fields']['credit'] = array(
      '#type' => 'select',
      '#options' => $text_fields,
      '#title' => 'Select field for media credit',
      '#description' => t('This field should be a text-like field'),
      '#default_value' => isset($this->options['timeline_fields']['credit']) ? $this->options['timeline_fields']['credit'] : '',
    );
    $form['timeline_fields']['thumbnail'] = array(
      '#type' => 'select',
      '#options' => $media_fields,
      '#title' => 'Select field for thumbnail',
      '#description' => t('Only image fields are currently supported'),
      '#default_value' => isset($this->options['timeline_fields']['thumbnail']) ? $this->options['timeline_fields']['thumbnail'] : '',
    );
    $form['timeline_fields']['era'] = array(
      '#type' => 'select',
      '#options' => $bool_fields,
      '#title' => 'Select field for type (era or title)',
      '#description' => t('This field should be a boolean (true/false) field'),
      '#default_value' => isset($this->options['timeline_fields']['era']) ? $this->options['timeline_fields']['era'] : '',
    );
    $form['timeline_fields']['tag'] = array(
      '#type' => 'select',
      '#options' => $text_fields,
      '#title' => 'Select field for tag',
      '#description' => t('This field should be a text-like field'),
      '#default_value' => isset($this->options['timeline_fields']['tag']) ? $this->options['timeline_fields']['tag'] : '',
    );
  }

  /**
   * Render the display in this style.
   */
  function render() {
    $view = $this->view;

    // We want to render some fields, because of field
    // rewriting and other field level processing
    $view->style_plugin->render_fields($view->result);

    $field_mapping = array(
      'startDate' => 'date',
      'endDate' => 'date',
      'headline' => 'headline',
      'text' => 'bodytext',
      'media' => 'media',
      'caption' => 'caption',
      'credit' => 'credit',
      'era' => 'era',
      'thumbnail' => 'thumbnail',
      'tag' => 'tag',
    );

    $link_text = isset($this->options['timeline_config']['link_text']) ? $this->options['timeline_config']['link_text'] : 'Read more';
    $rows = array();

    // TODO: Figure out how to detect field types and different rendering methods for them
    $media_field_type = isset($this->options['timeline_fields']['media']) ? $view->field[$this->options['timeline_fields']['media']]->field_info['type'] : NULL;

    // Build a TimelineJS friendly array from the views data
    foreach($view->result as $count => $row) {
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
              $fields[$target_field] = array(
                'field' => $this->options['timeline_fields'][$source_field],
                'raw' => $view->style_plugin->get_field_value($count, $this->options['timeline_fields'][$source_field]),
              );
            }
          }
        }
      }

      foreach ($fields as $key => $field_data) {
        $field = $field_data['field'];
        $fields[$key] = $field_data['raw'];

        if (isset($view->field[$field]->field_info['type'])) {
          $type = $view->field[$field]->field_info['type'];
          switch($type) {
            case 'text_with_summary':
              $fields[$key] = $view->style_plugin->rendered_fields[$count][$field];
              break;
            case 'date':
              if (is_array($fields[$key])) {
                $date_tmp = array_shift($fields[$key]);
                $fields['startDate'] = strtotime($date_tmp['value']);
                if (isset($date_tmp['value2'])) {
                  $fields['endDate'] = strtotime($date_tmp['value2']);
                } else {
                  $fields['endDate'] = $fields['startDate'];
                }
                $fields['startDate'] = format_date($fields['startDate'], 'custom', 'Y,m,d');
                $fields['endDate'] = format_date($fields['endDate'], 'custom', 'Y,m,d');
              }
              break;
            case 'image':
              $image_style = image_style_load($view->field[$field]->options['settings']['image_style']);
              if (is_array($fields[$key])) {
                $field_tmp = array_shift($fields[$key]);
                $preview_file = image_style_url($image_style['name'], $field_tmp['uri']);
                image_style_create_derivative($image_style, $field_tmp['uri'], $preview_file);
                $fields[$key] = $preview_file;
              }
              break;
          }
        }
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

      if (isset($fields['era']) && ($fields['era'] == TRUE || $fields['era'] == 'era')) {
        $era[] = array(
          'startDate' => isset($fields['startDate']) ? $fields['startDate'] : '',
          'endDate' => isset($fields['endDate']) ? $fields['endDate'] : '',
          'headline' => isset($fields['headline']) ? $fields['headline'] : '',
          'text' => isset($fields['text']) ? $fields['text'] : '',
          'tag' => isset($fields['tag']) ? $fields['tag'] : '',
        );
      } else {
        // Combine the results array with processed row data
        $date[] = array(
          'startDate' => isset($fields['startDate']) ? $fields['startDate'] : '',
          'endDate'   => isset($fields['endDate']) ? $fields['endDate'] : '',
          'headline'  => isset($fields['headline']) ? $fields['headline'] : '',
          'text'      => isset($fields['text']) ? $fields['text'] : '',
          'tag'       => isset($fields['tag']) ? $fields['tag'] : '',
          'asset' => array(
            'media'     => isset($fields['media']) ? $fields['media'] : '',
            'thumbnail' => isset($fields['thumbnail']) ? $fields['thumbnail'] : '',
            'credit'    => isset($fields['credit']) ? $fields['credit'] : '',
            'caption'   => isset($fields['caption']) ? $fields['caption'] : ''
          ),
        );
      }
    }

    // Let modules alter timeline data before rendering by implementing
    // hook_views_timelinejs_data_alter(&$rows, $view)
    // TODO: Re enable this later.
    //drupal_alter('views_timelinejs_data', $rows, clone $view);

    // Prepare data array that TimelineJS understands
    $data = array(
      'type' => 'timeline',
      'embed_path' => libraries_get_path('timeline') . '/compiled/',
      'id' => drupal_html_class('storyjs-' . user_password(8)),
      'embed_id' => 'timelinejs_' . $view->name . '_' . $view->current_display,
      'lang' => $GLOBALS['language']->language,
      'width' => $this->options['timeline_config']['width'],
      'height' => $this->options['timeline_config']['height'],
      'start_zoom_adjust' => $this->options['timeline_config']['start_zoom_adjust'],
      'start_at_slide' => $this->options['timeline_config']['start_at_slide'],
      'start_at_end' => (bool) $this->options['timeline_config']['start_at_end'],
      'source' => array(
        'timeline' => array(
          'headline' => $this->options['timeline_config']['headline'],
          'type' => 'default',
          'date' => $date,
          'era'  => $era,
        ),
      ),
    );

    // Skip rendering if view is being edited or previewed
    if(!$view->editing) {
      return theme('views_timelinejs', array('timelinejs' => $data));
    }
    else {
      //return t('TimelineJS style does not support preview mode.');
      return '<pre>'.print_r($data, 1).'</pre>';
    }
  }
}