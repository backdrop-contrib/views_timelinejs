Drupal.behaviors.timelineJS = {
  attach: function(context, settings) {
    // TODO: Make this work with multiple timelines per page
    if(VMM.Timeline && Drupal.settings.timelineJS['source']) {
      var timeline = new VMM.Timeline(
        Drupal.settings.timelineJS['embed_id'],
        Drupal.settings.timelineJS['width'],
        Drupal.settings.timelineJS['height']
      );
      timeline.init({
        source: Drupal.settings.timelineJS['source'],
        lang: Drupal.settings.timelineJS['lang'],
      });
    }
  }
}

