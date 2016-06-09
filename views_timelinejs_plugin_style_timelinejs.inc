<?php

/**
 * Style plugin to render items as TimelineJS3 slides.
 *
 * @ingroup views_style_plugins
 */
class views_timelinejs_plugin_style_timelinejs extends views_plugin_style {

  /**
   * The row index of the slide at which the timeline should first be rendered.
   */
  protected $start_slide_index;

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['timeline_config'] = array(
      'contains' => array(
        'width' => array('default' => '100%'),
        'height' => array('default' => '500px'),
        'hash_bookmark' => array('default' => ''),
        'start_at_end' => array('default' => ''),
        'scale_factor' => array('default' => '2'),
        'language' => array('default' => ''),
      ),
    );
    $options['additional_config'] = array(
      'contains' => array(
        'font' => array('default' => ''),
        'start_at_current' => array('default' => ''),
      ),
    );
    $options['timeline_fields'] = array(
      'contains' => array(
        'caption' => array('default' => ''),
        'credit' => array('default' => ''),
        'media' => array('default' => ''),
        'group' => array('default' => ''),
        'date' => array('default' => ''),
        'text' => array('default' => ''),
        'headline' => array('default' => ''),
        'background' => array('default' => ''),
      ),
    );
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    $initial_labels = array('' => t('- None -'));
    $view_fields_labels = $this->display->handler->get_field_labels();
    $view_fields_labels = array_merge($initial_labels, $view_fields_labels);

    // Timeline general configuration.
    $form['timeline_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('TimelineJS Options'),
      '#description' => t('Each of these settings maps directly to one of the TimelineJS presentation options.  See the <a href="@options-doc">options documentation page</a> for additional information.', array('@options-doc' => 'https://timeline.knightlab.com/docs/options.html')),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_config']['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width of the timeline'),
      '#description' => t('The width of the timeline, e.g. "100%" or "650px".'),
      '#default_value' => $this->options['timeline_config']['width'],
      '#size' => 10,
      '#maxlength' => 10,
    );
    $form['timeline_config']['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height of the timeline'),
      '#description' => t('The height of the timeline, e.g. "100%" or "650px".'),
      '#default_value' => $this->options['timeline_config']['height'],
      '#size' => 10,
      '#maxlength' => 10,
    );
    $form['timeline_config']['hash_bookmark'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add hash bookmarks'),
      '#description' => t('On each slide, a # will be added to the end of the url in the url bar. These urls are bookmarkable, so you can share or return to the same place in the timeline later.'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['timeline_config']['hash_bookmark'],
    );
    $form['timeline_config']['scale_factor'] = array(
      '#type' => 'select',
      '#title' => t('Scale factor'),
      '#description' => t('How many screen widths wide the timeline should be at first presentation.'),
      '#options' => array(
        '1' => t('1'),
        '2' => t('2'),
        '3' => t('3'),
        '4' => t('4'),
        '5' => t('5'),
        '6' => t('6'),
        '7' => t('7'),
        '8' => t('8'),
        '9' => t('9'),
      ),
      '#default_value' => $this->options['timeline_config']['scale_factor'],
    );
    $form['timeline_config']['start_at_end'] = array(
      '#type' => 'checkbox',
      '#title' => t('Start at the end'),
      '#description' => t('Loads the timeline on the last slide.'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['timeline_config']['start_at_end'],
    );
    $form['timeline_config']['language'] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#title' => t('Language'),
      '#description' => t('The <a href="@language-list">language code</a>. Leave blank for the site language.', array('@language-list' => 'https://github.com/NUKnightLab/TimelineJS#language')),
      '#default_value' => $this->options['timeline_config']['language'],
    );

    // Timeline additional configuration.
    $form['additional_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('Additional Options'),
      '#description' => t('These settings include extra options to control the TimelineJS presentation or options unique to this plugin.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['additional_config']['font'] = array(
      '#type' => 'select',
      '#title' => t('Font set'),
      '#description' => t('TimelineJS3 offers several pre-selected font sets.  If a set is selected its CSS file will be downloaded from the CDN.'),
      '#options' => array_merge($initial_labels, _views_timelinejs_list_font_sets()),
      '#default_value' => $this->options['additional_config']['font'],
    );
    $form['additional_config']['start_at_current'] = array(
      '#type' => 'checkbox',
      '#title' => t('Start at Current'),
      '#description' => t('Loads the timeline on the slide closest to the current time.'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['additional_config']['start_at_current'],
    );

    // Field mapping.
    $form['timeline_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Field mappings'),
      '#description' => t('Map your Views data fields to TimelineJS slide object properties.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_fields']['headline'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Headline'),
      '#required' => TRUE,
      '#description' => t('The selected field may contain any text, including HTML markup.'),
      '#default_value' => $this->options['timeline_fields']['headline'],
    );
    $form['timeline_fields']['text'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Body text'),
      '#description' => t('The selected field may contain any text, including HTML markup.'),
      '#default_value' => $this->options['timeline_fields']['text'],
    );
    $form['timeline_fields']['start_date'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Start date'),
      '#required' => TRUE,
      '#description' => t('The selected field should contain a string representing a date conforming to a <a href="@php-manual">PHP supported date and time format</a>.', array('@php-manual' => 'http://php.net/manual/en/datetime.formats.php')),
      '#default_value' => $this->options['timeline_fields']['start_date'],
    );
    $form['timeline_fields']['end_date'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('End date'),
      '#description' => t('The selected field should contain a string representing a date conforming to a <a href="@php-manual">PHP supported date and time format</a>.', array('@php-manual' => 'http://php.net/manual/en/datetime.formats.php')),
      '#default_value' => $this->options['timeline_fields']['end_date'],
    );
    $form['timeline_fields']['background'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Background image'),
      '#description' => t('The selected field should contain a raw URL to an image.  Special handling is included for Image fields because they have no raw URL formatter.'),
      '#default_value' => $this->options['timeline_fields']['background'],
    );
    $form['timeline_fields']['media'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Media URL'),
      '#description' => t('The selected field should contain a raw URL to a media resource.  See the <a href="@media-documentation">media types documentation</a> for a list of supported types.  Blockquote and iframe HTML are not currently supported by this plugin.  Special handling is included for Image fields because they have no raw URL formatter.', array('@media-documentation' => 'https://timeline.knightlab.com/docs/media-types.html')),
      '#default_value' => $this->options['timeline_fields']['media'],
    );
    $form['timeline_fields']['credit'] = array(
      '#type' => 'select',
      '#title' => t('Media Credit'),
      '#description' => t('The selected field may contain any text, including HTML markup.'),
      '#options' => $view_fields_labels,
      '#default_value' => $this->options['timeline_fields']['credit'],
    );
    $form['timeline_fields']['caption'] = array(
      '#type' => 'select',
      '#title' => t('Media Caption'),
      '#description' => t('The selected field may contain any text, including HTML markup.'),
      '#options' => $view_fields_labels,
      '#default_value' => $this->options['timeline_fields']['caption'],
    );
    $form['timeline_fields']['group'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Group'),
      '#description' => t('The selected field may contain any text. If present, TimelineJS will organize events with the same value for group to be in the same row or adjacent rows, separate from events in other groups. The common value for the group will be shown as a label at the left edge of the navigation.'),
      '#default_value' => $this->options['timeline_fields']['group'],
    );
  }

  /**
   * {@inheritdoc}
   */
  function validate() {
    $errors = parent::validate();

    // Validate that fields have been assigned to the required options.
    foreach (array('start_date', 'headline') as $required_option) {
      if (empty($this->options['timeline_fields'][$required_option])) {
        $errors[] = t('The TimelineJS plugin requires specifying which views fields to use for the event slides.');
        break;
      }
    }
    return $errors;
  }

  /**
   * {@inheritdoc}
   */
  function render() {
    $slides = array();

    // Render slide arrays from the views data.
    foreach ($this->view->result as $row_index => $row) {
      $this->view->row_index = $row_index;
      $slide = $this->render_slide($row);
      // Ensure the slide has a start date.
      if (!empty($slide['start_date'])) {
        $slides[] = $slide;
      }
    }
    unset($this->view->row_index);

    // Prepare a data array that TimelineJS3 understands.
    $data = array(
      'scale' => 'human',
      'events' => $slides,
    );
    if (!empty($this->options['additional_config']['start_at_current'])) {
      $data['timeline']['start_at_current'] = $this->start_slide_index;
    }

    // Skip theming if the view is being edited or previewed.
    if ($this->view->editing) {
      return '<pre>' . print_r($data, 1) . '</pre>';
    }

    return theme('views_timelinejs', array(
      'view' => $this->view,
      'options' => $this->options,
      'rows' => $data,
    ));
  }

  /**
   * Renders a TimelineJS slide from a views data row.
   *
   * @param type $row
   *   A views result row.
   *
   * @return array
   *   A array representing an individual TimelineJS slide.
   */
  protected function render_slide($row) {
    // Store the row index so the code is a little easier to read.
    $row_index = $this->view->row_index;

    $slide = array();

    if ($this->options['timeline_fields']['headline']) {
      $slide['text']['headline'] = $this->get_field($row_index, $this->options['timeline_fields']['headline']);
    }

    if ($this->options['timeline_fields']['text']) {
      $slide['text']['text'] = $this->get_field($row_index, $this->options['timeline_fields']['text']);
    }

    if ($this->options['timeline_fields']['group']) {
      $slide['group'] = $this->get_field($row_index, $this->options['timeline_fields']['group']);
    }

    if ($this->options['timeline_fields']['start_date']) {
      $start_date_value = $this->get_field($row_index, $this->options['timeline_fields']['start_date']);
      if (!empty($start_date_value)) {
        // Format the date for TimelineJS3.
        $start_date = new TimelineDate($start_date_value);
        $slide['start_date'] = $start_date->getTimelineDateArray();

        // Check to see if this slide should be the start slide.
        $this->check_start_slide($start_date);
      }
    }

    if ($this->options['timeline_fields']['end_date'] && !empty($start_date_value)) {
      $end_date_value = $this->get_field($row_index, $this->options['timeline_fields']['end_date']);

      // Don't render end dates that are the same as the start date.  TimelineJS
      // won't display them anyway, but skipping them can make the rendered data
      // array smaller.
      if (!empty($end_date_value) && $start_date_value !== $end_date_value) {
        // Format the date for TimelineJS3.
        $end_date = new TimelineDate($end_date_value);
        $slide['end_date'] = $end_date->getTimelineDateArray();
      }
    }

    if ($this->options['timeline_fields']['background']) {
      $background_url_value = $this->get_field($row_index, $this->options['timeline_fields']['background']);

      // Special handling because core Image fields have no raw URL formatter.
      // Check to see if we don't have a raw URL.
      if (!filter_var($background_url_value, FILTER_VALIDATE_URL)) {
        // Attempt to extract a URL from the string.
        $background_url_value = $this->extract_url($background_url_value);
      }

      if (!empty($background_url_value)) {
        $slide['background']['url'] = $background_url_value;
      }
    }

    // @todo: Add support for text containing a blockquote or iframe.
    if ($this->options['timeline_fields']['media']) {
      $media_url_value = $this->get_field($row_index, $this->options['timeline_fields']['media']);

      // Special handling because core Image fields have no raw URL formatter.
      // Check to see if we don't have a raw URL.
      if (!filter_var($media_url_value, FILTER_VALIDATE_URL)) {
        // Attempt to extract a URL from the string.
        $media_url_value = $this->extract_url($media_url_value);
      }

      if (!empty($media_url_value)) {
        $slide['media']['url'] = $media_url_value;
        $slide['media']['thumbnail'] = $media_url_value;
      }
    }

    if ($this->options['timeline_fields']['caption'] && !empty($media_url_value)) {
      $caption_value = $this->get_field($row_index, $this->options['timeline_fields']['caption']);
      if (!empty($caption_value)) {
        $slide['media']['caption'] = $this->get_field($row_index, $this->options['timeline_fields']['caption']);
      }
    }

    if ($this->options['timeline_fields']['credit'] && !empty($media_url_value)) {
      $credit_value = $this->get_field($row_index, $this->options['timeline_fields']['credit']);
      if (!empty($credit_value)) {
        $slide['media']['credit'] = $this->get_field($row_index, $this->options['timeline_fields']['credit']);
      }
    }

    return $slide;
  }

  /**
   * Checks a slide date to see if it should be displayed first in the timeline.
   *
   * @param DateTime $date
   *   A date from a TimelineJS slide.
   */
  protected function check_start_slide(DateTime $date) {
    static $smallest_difference;
    if (!isset($smallest_difference)) {
      $smallest_difference = NULL;
    }

    $timestamp = $date->getTimestamp();
    // Return if the date was prior to the UNIX Epoch.
    if ($timestamp === FALSE) {
      return;
    }

    // Calculate the absolute difference between the current time and the date.
    $difference = abs(time() - $timestamp);

    // Update the start slide index if this date is closer to the current time.
    if ($smallest_difference == NULL || $difference < $smallest_difference) {
      $smallest_difference = $difference;
      $this->start_slide_index = $this->view->row_index;
    }
  }

  /**
   * Searches a string for HTML attributes that contain URLs and returns them.
   *
   * This will search a string which is presumed to contain HTML for anchor or
   * image tags.  It will return the href or src attribute of the first one it
   * finds.
   *
   * This is basically special handling for core Image fields.  There is no
   * built-in field formatter for outputting a raw URL from an image.  This
   * method allows image fields to "just work" as sources for TimelineJS media
   * and background image URLs.  Anchor tag handling was added for people who
   * forget to output link fields as plain text URLs.
   *
   * @param string $html
   *   A string that contains HTML.
   *
   * @return string
   *   A URL if one was found in the input string, empty if not.
   */
  protected function extract_url($html) {
    if (!empty($html)) {
      $document = new DOMDocument();
      $document->loadHTML($html);

      // Check for anchor tags.
      $anchor_tags = $document->getElementsByTagName('a');
      if ($anchor_tags->length) {
        return $anchor_tags->item(0)->getAttribute('href');
      }

      // Check for image tags.
      $image_tags = $document->getElementsByTagName('img');
      if ($image_tags->length) {
        return $image_tags->item(0)->getAttribute('src');
      }
    }
    return '';
  }

}
