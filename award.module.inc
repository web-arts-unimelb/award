<?php
/**
 * @file
 */

/**
 * Implements hook_form_alter()
 */
function award_form_alter(&$form, &$form_state, $form_id) {
  // The views blocks whose exposed forms need modification.
  $views = array('views-exposed-form-awards-block-2', 'views-exposed-form-awards-block-3', 'views-exposed-form-awards-block-4', 'views-exposed-form-awards-block-5');
  
  if ($form_id == 'views_exposed_form' && !empty($form['#id']) && in_array($form['#id'], $views)) {
    // Make the select list of study areas a bit smaller.
    $form['field_award_study_area_tid']['#size'] = 4;

		// Change the keyword search <input title="" > 
		$form['keys']['#attributes']['title'] = t('Full word & correct spelling must be entered.');
  }
 
  // Set default search term in award type filter
  if(isset($form['#id']))
  {
  	if($form['#id'] == 'views-exposed-form-awards-page-5') 
		{
			// Advance search scholarship
		
			// Reset if select Any in study area filter
			_reset_study_area_filter($form_state);
		
			// Set default award type search to scholarship
	 		if(empty($_GET['field_award_type_value_1']))
	 		{
				$form_state['input']['field_award_type_value_1'] = 'scholarship';
			}
	 	}
		else if($form['#id'] == 'views-exposed-form-awards-block-4')
		{
			// Advance search scholarship block

      // Reset if select Any in study area filter
      _reset_study_area_filter($form_state);

			_build_study_level_markup($form);

      // Set default award type search to scholarship
      if(empty($_GET['field_award_type_value']))
      {
        $form_state['input']['field_award_type_value'] = 'scholarship';
      }
      
      // Date filter
      // Change the layout
      if(isset($form['field_award_application_date_value'])) {
				$options = array(
					'any' => '- Any -',
					//'open_soon' => 'Open soon', # We comment it out, but we may use it later.
					'open' => 'Open',
					'close' => 'Closed',
				);
		
				$tmp_array = array(
					'#type' => 'select',
					'#options' => $options,
					'#default_value' => 'any',
				);
			
				$form['field_award_application_date_value']['value'] = $tmp_array;
		  }
		  
		}
	 	else if($form['#id'] == 'views-exposed-form-awards-block-7')
	 	{
	 		// Normal prize search
	 		_correct_form_action_url($form);
		}
	 	else if($form['#id'] == 'views-exposed-form-awards-block-5') 
		{
			// Advance prize search
			_reset_study_area_filter($form_state);
		
			_build_study_level_markup($form);
		
			// Set default award type search to prize
	 		if(empty($_GET['field_award_type_value']))
	 		{
				$form_state['input']['field_award_type_value'] = 'prize';
			}
			
			_correct_form_action_url($form);
	 	}
		else if($form['#id'] == 'views-exposed-form-awards-block-2') 
		{
			// Advance grant search
		
			_reset_study_area_filter($form_state);
		
			_build_study_level_markup($form);
		
			// Set default award type search to grant
	 		if(empty($_GET['field_award_type_value']))
	 		{
				$form_state['input']['field_award_type_value'] = 'grant';
			}
	 	}
 	}
 	
 	/* Start select / unselect all study area */
 	if($form_id == 'award_node_form' && $form['#node_edit_form '] = TRUE) {
		
		drupal_add_js("
			jQuery(document).ready(function() {
			  var award_num_of_checkbox = jQuery('input[name^=\"field_award_study_area\"]').length;
			  var award_count_use_checkbox = 0;
			  
			  jQuery('input[name^=\"field_award_study_area\"]').each(function(){
					if(this.checked) {
						++award_count_use_checkbox;
					}	    	
			  });
			  
			  if(award_count_use_checkbox == award_num_of_checkbox) {
			  	jQuery('input[name=\"checkall\"]').attr('checked', true);
			  }
			});
			
			function checkUncheckAll(theElement) {
			  jQuery('input[name^=\"field_award_study_area\"]').each(function(){  
	      	this.checked = theElement.checked; 
			  });
			}	
		", 'inline');

		// Change order
		$field_award_study_area_orig_weight = $form['field_award_study_area']['#weight'];
		$form['field_award_study_area']['#weight'] = $form['field_award_study_area']['#weight'] + 1;

		// Only repository site has this field
		if(isset($form['field_syndication_site'])) {	
			$form['field_syndication_site']['#weight'] = $form['field_syndication_site']['#weight'] + 1;
		}

		$form['checkall'] = array(
		  '#type' => 'checkbox',
		  '#title' => t('Select / Unselect all study area'),
		  '#attributes' => array('onclick' => 'checkUncheckAll(this);'),
		  '#weight' => $field_award_study_area_orig_weight,
		);
	}
 	/* End select / unselect all study area */
}

/**
 * Implements hook_views_pre_render().
 */
function award_views_pre_render(&$view) {
  $select_all = 'select all';
  $select_all_display = t('Any');

  if($view->name == "awards") {
    $results = &$view->result;

		$study_area_obj = taxonomy_vocabulary_machine_name_load("study_area");
		$tree = taxonomy_get_tree($study_area_obj->vid);
		$full_item_num = count($tree);

		// Loop through each displayed award.
		foreach($results as $key => $result) {
			$num_of_study_area = count($results[$key]->field_field_award_study_area);

			if($full_item_num <= $num_of_study_area || $num_of_study_area == 0) {
        $results[$key]->field_field_award_study_area = array(
          0 => array(
            'rendered' => array(
              '#markup' => $select_all_display
            ),
          ),
        );	
			}
		}
		
		/*
    foreach($results as $key => $result) {
      foreach($results[$key]->field_field_award_study_area as $item) {
        if( strtolower($item['rendered']['#markup']) == $select_all ) {
          $results[$key]->field_field_award_study_area = array(
            0 => array(
              'rendered' => array(
                '#markup' => $select_all_display
              ),
            ),
          );
        }
      }
    }
    */
  }
}

// Remove duplicated view search results
// http://drupal.stackexchange.com/questions/79965/how-to-remove-duplicate-from-views-result-page
function award_query_alter(QueryAlterableInterface $query) { 
  if(isset($query->alterMetaData)) {
    if(isset($query->alterMetaData['view'])) {
			// Use devel to see which views
      if($query->alterMetaData['view']->name == 'awards') {     
        $fields =& $query->getGroupBy();
        // Tried various fields to check which was the field creating the problem.
        unset($fields['score']);
        $query->groupBy('nid');
      }
    }
  }
}

function unimelb_preprocess_views_exposed_form(&$vars, $hook) 
{
	if(
		$vars['form']['#id'] == 'views-exposed-form-awards-page-5' or
		$vars['form']['#id'] == 'views-exposed-form-awards-block-4' or
		$vars['form']['#id'] == 'views-exposed-form-awards-block-5' or
		$vars['form']['#id'] == 'views-exposed-form-awards-block-2' 
	) 
	{
		foreach($vars['widgets'] as $id => &$widget) 
		{
  		switch ($id) 
  		{
        case 'filter-field_award_study_area_tid':
     			$widget->widget = _build_taxonomy_dropdown($widget->widget);
          break;

      }
  	}
	}
}

function _build_taxonomy_dropdown($input)
{
	$html = "";
	$option_html = _build_dropdown_option($input);

	// NOTE: Hard code
	$html = '
		<div class="form-item form-type-select form-item-field-award-study-area-tid">
			<select class="form-select" size="9" id="edit-field-award-study-area-tid" name="field_award_study_area_tid[]" multiple="multiple">
	';

	
	$html .= $option_html;	
		
	$html .= '
			</select>
		</div>	
	';

	return $html;
}

function _build_dropdown_option($input)
{
	$option_html = "<option value='All'>- Any -</option>";
	//$option_html = "";
	
	$is_select_all_condi = true;
	
	$doc = new DOMDocument();
	$doc->loadHTML($input);

	$xpath = new DOMXpath($doc);
	$options = $xpath->query("*/div/select/option");

	foreach($options as $option) 
	{
  	$option_value = $option->getAttribute('value');
  	$option_content = $option->nodeValue;
  
  	if( $is_select_all_condi && _is_select_all($option_content) )
  	{
  		// Skip to generate the option tag
  		$is_select_all_condi = false;
  	}
  	elseif(empty($option_content))
  	{
  		// Skip if node value is empty
  	}
		elseif( _is_child($option_content) )
		{
			$option_content = substr_replace($option_content, '&nbsp;', 1, 0);
			$option_html .= "<option value=\"$option_value\">&nbsp;&nbsp;$option_content</option>";
		}
		else
		{
			$option_html .= "<option class=\"award_study_area_option_tag\" value=\"$option_value\">$option_content</option>";
			//$option_html .= "<option value=\"$option_value\">$option_content</option>";
		}
	}
	
	return $option_html;
}

function _is_select_all($value = "")
{
	if(strtolower($value) == "select all")
	{
		return true;
	}
	else
	{
		return false;
	}
}

function _is_child($value = "")
{
	if($value[0] == "-")
	{
		return true;
	}
	else
	{
		return false;
	}
}

function _reset_study_area_filter(&$form_state)
{
	if(isset($form_state['input']['field_award_study_area_tid'][0]))
	{
		if($form_state['input']['field_award_study_area_tid'][0] == 'All')
		{
			$form_state['input']['field_award_study_area_tid'] = array();
		}
	}
}


// http://drupal.stackexchange.com/questions/3590/adding-an-all-option-to-a-views-exposed-filter
function _build_study_level_markup(&$form) {
	$form['field_award_study_level_value']['#options'] = array("All" => t("- Any -")) + $form['field_award_study_level_value']['#options'];
}


// Not the exact issue, but with the idea
// http://drupal.org/node/1783968
function _correct_form_action_url(&$form)
{
	if($form['#action'] == "/scholarships/grants-list")
	{
		$form['#action'] = "/scholarships/prize-list";	
	}
}


// hook_views_query_alter
function award_views_query_alter(&$view, &$query) {
	
	if($view->name == 'awards') {
		if(isset($view->exposed_raw_input['field_award_application_date_value'])) {
			$open_date_status = $view->exposed_raw_input['field_award_application_date_value']['value'];
			
			foreach ($query->where as $key_1 => &$condition_group) {
			  foreach ($condition_group['conditions'] as $key_2 => &$condition) {
			  
			  	// Sample string
					//$dummy_field_name = "DATE_FORMAT(field_data_field_award_application_date.field_award_application_date_value, '%Y-%m-%d') = :field_data_field_award_application_date_field_award_application_date_value";
					
					// https://drupal.org/comment/4094520#comment-4094520
					$needle = 'field_data_field_award_application_date.field_award_application_date_value';
			    if (isset($condition['field']) && is_string($condition['field']) && strstr($condition['field'], $needle)) {
			    	if($open_date_status == 'any') {
			    		unset($query->where[$key_1]['conditions'][$key_2]);
			    	} 
			    	elseif($open_date_status == 'open_soon') {
			    	
					  	$the_field = "DATE_FORMAT(field_data_field_award_application_date.field_award_application_date_value, '%Y-%m-%d') > :field_data_field_award_application_date_field_award_application_date_value";
					  	
					  	$today = date('Y-m-d');
					  
					  	$the_value =  array(':field_data_field_award_application_date_field_award_application_date_value' => $today);
					  
					  	$condition = array(
						    'field' => $the_field,
						    'value' => $the_value,
						    'operator' => 'formula',
						  );
						  
			    	}
			    	elseif($open_date_status == 'open') {
			    	
			    		$today = date('Y-m-d');
			    		
			    		$the_value =  array(':field_data_field_award_application_date_field_award_application_date_value' => $today);
			    	
			    		// Greater
							$the_field = "DATE_FORMAT(field_data_field_award_application_date.field_award_application_date_value, '%Y-%m-%d') <= :field_data_field_award_application_date_field_award_application_date_value";

			    		$condition = array(
						    'field' => $the_field,
						    'value' => $the_value,
						    'operator' => 'formula',
						  );
			    		
			    		
			    		// Less
			    		$the_field_2 = "DATE_FORMAT(field_data_field_award_application_date.field_award_application_date_value2, '%Y-%m-%d') >= :field_data_field_award_application_date_field_award_application_date_value";
			    		
			    		$new_condition = array(
						    'field' => $the_field_2,
						    'value' => $the_value,
						    'operator' => 'formula',
						  );
			    		
			    		$new_key = $key_2 + 1;
			    		$query->where[$key_1]['conditions'][$new_key] = $new_condition;
			    		
			    	}
			    	elseif($open_date_status == 'close') {
			    	
			    		$the_field = "DATE_FORMAT(field_data_field_award_application_date.field_award_application_date_value2, '%Y-%m-%d') < :field_data_field_award_application_date_field_award_application_date_value";
					  	
					  	$today = date('Y-m-d');
					  
					  	$the_value =  array(':field_data_field_award_application_date_field_award_application_date_value' => $today);
					  
					  	$condition = array(
						    'field' => $the_field,
						    'value' => $the_value,
						    'operator' => 'formula',
						  );
						  
			    	}
			    
			    	//dsm($open_date_status);
			    	//dsm($query->where);
			 
			    }
			  }
			}
		}
		
		// Remove a join & where condition
		if(isset($view->exposed_raw_input['field_award_study_level_value'])) {
			// It is any study level
			if(isset($view->exposed_raw_input['field_award_study_level_value']['All'])) {
				foreach($query->where as $key_1 => &$condition_group) {
			  	foreach($condition_group['conditions'] as $key_2 => &$condition) {
						// https://drupal.org/node/1062054#comment-4094520
						// Because we eventually want to compare string, so make sure it is string.
			  		if(
								isset($condition['field']) && 
								is_string($condition['field']) && 
								($condition['field'] == 'field_data_field_award_study_level.field_award_study_level_value')
						) {
			  			unset($query->table_queue['field_data_field_award_study_level']);
			  			unset($condition_group['conditions'][$key_2]);
			  		}
			  	}
			  }
			}
		}
	}
}
