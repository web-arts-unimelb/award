<?php
/**
 * @file
 * award.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function award_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Award',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_bundle:node',
          'settings' => array(
            'type' => array(
              'award' => 'award',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '374bbf5e-7978-4b23-a949-a86f049837df';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-5ee41f87-8484-4eb4-9eac-300de2c117bc';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'views-awards-block_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '5ee41f87-8484-4eb4-9eac-300de2c117bc';
    $display->content['new-5ee41f87-8484-4eb4-9eac-300de2c117bc'] = $pane;
    $display->panels['center'][0] = 'new-5ee41f87-8484-4eb4-9eac-300de2c117bc';
    $pane = new stdClass();
    $pane->pid = 'new-081933b1-aa77-4ef1-8e89-c420b3df1fd9';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '081933b1-aa77-4ef1-8e89-c420b3df1fd9';
    $display->content['new-081933b1-aa77-4ef1-8e89-c420b3df1fd9'] = $pane;
    $display->panels['center'][1] = 'new-081933b1-aa77-4ef1-8e89-c420b3df1fd9';
    $pane = new stdClass();
    $pane->pid = 'new-08bd64fe-2ebf-47ab-b43f-3597a436a853';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_award_conditions';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '08bd64fe-2ebf-47ab-b43f-3597a436a853';
    $display->content['new-08bd64fe-2ebf-47ab-b43f-3597a436a853'] = $pane;
    $display->panels['center'][2] = 'new-08bd64fe-2ebf-47ab-b43f-3597a436a853';
    $pane = new stdClass();
    $pane->pid = 'new-8d4efb9f-1aa0-4eed-8a32-d86a3e32b3ce';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_award_application_process';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '8d4efb9f-1aa0-4eed-8a32-d86a3e32b3ce';
    $display->content['new-8d4efb9f-1aa0-4eed-8a32-d86a3e32b3ce'] = $pane;
    $display->panels['center'][3] = 'new-8d4efb9f-1aa0-4eed-8a32-d86a3e32b3ce';
    $pane = new stdClass();
    $pane->pid = 'new-75422c87-e839-4f9f-a47f-98a178261f55';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_award_enquire_now';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
      'formatter' => 'email_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '75422c87-e839-4f9f-a47f-98a178261f55';
    $display->content['new-75422c87-e839-4f9f-a47f-98a178261f55'] = $pane;
    $display->panels['center'][4] = 'new-75422c87-e839-4f9f-a47f-98a178261f55';
    $pane = new stdClass();
    $pane->pid = 'new-cb9d91e2-b265-4e26-9017-d7c1cea8376f';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_award_submissions';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'link_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = 'cb9d91e2-b265-4e26-9017-d7c1cea8376f';
    $display->content['new-cb9d91e2-b265-4e26-9017-d7c1cea8376f'] = $pane;
    $display->panels['center'][5] = 'new-cb9d91e2-b265-4e26-9017-d7c1cea8376f';
    $pane = new stdClass();
    $pane->pid = 'new-0beff16f-2dd6-4513-887e-1c0c5e21c2c1';
    $pane->panel = 'center';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'The judges\' decision',
      'title' => '',
      'body' => '<p style="font-size:smaller;">The judges\' decision will be final and the University reserves the right not to award the prize in the event it is considered that no work of sufficient merit has been submitted. Winning applicants please note the University of Melbourne reserves the right to publish the name of the winning applicant on its websites and other University of Melbourne publications.</p>',
      'format' => 'complete_full_html',
      'substitute' => 1,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 6;
    $pane->locks = array();
    $pane->uuid = '0beff16f-2dd6-4513-887e-1c0c5e21c2c1';
    $display->content['new-0beff16f-2dd6-4513-887e-1c0c5e21c2c1'] = $pane;
    $display->panels['center'][6] = 'new-0beff16f-2dd6-4513-887e-1c0c5e21c2c1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context'] = $handler;

  return $export;
}
