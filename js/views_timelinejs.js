Drupal.behaviors.timelineJS = {
  attach: function(context, settings) {
    // TODO: Make this work with multiple timelines per page
    if(Drupal.settings.timelineJS['source']) {
      createStoryJS({
        type: 'timeline',
        width: Drupal.settings.timelineJS['width'],
        height: Drupal.settings.timelineJS['height'],
        source: Drupal.settings.timelineJS['source'],
        embed_id: Drupal.settings.timelineJS['embed_id'],
        lang: Drupal.settings.timelineJS['lang'],
      });
    }
  }
}

