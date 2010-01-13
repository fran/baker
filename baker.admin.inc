<?php

function baker_admin_delete_form()
{
  $form = array();
  $bid = arg(4);
  if (isset($bid)) {
    $form['bid'] = array(
      '#type' => 'hidden',
      '#value' => $bid,
    );
    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    );
  }

}


function baker_admin_form()
{ 

  $form = array();

  $bid = arg(4);
  if (isset($bid)) {
    $customItem = _baker_get_custom_breadcrumb($bid);
    $form['bid'] = array(
      '#type' => 'hidden',
      '#value' => $bid,
    );
  }
    
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Source'),
    '#required' => True,
    '#description' => t('Define the Url to assign the title that will be defined.'),
    '#default_value' => $bid ? $customItem->url : NULL,
  );
  
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => True,
    '#description' => t('Define the title of the url defined in the previous input.'),
    '#default_value' => $bid ? $customItem->title : NULL,
  );
  
  
  $form['redirect'] = array(
    '#type' => 'textfield',
    '#title' => t('Target'),
    '#required' => False,
    '#description' => t('Define the Url to redirect when click the breadcrumb'),
    '#default_value' => $bid ? $customItem->redirect : NULL,
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  
  return $form;
}

/**
 * Generate the HTML code for the administation page, the urls/titles table and the acctions to manage them.
 *
 * @return The view of the page
 * @author fran
 **/
function baker_administration_page()
{
  $output = _baker_popups_links();
  $output .= _baker_administration_table();
  
  return $output;
}


/**
 * Generate the html code that contains the custom breadcrumbs.
 *
 * @return $output : html code with the table
 * @author fran
 **/
function _baker_administration_table()
{
  // get the custom breadcrumbs from baker
  $sql = "select * from baker";
  $result = db_query($sql);

  $header = array(t("URL"), t("Title"), t("Redirection"), t("Actions"));
  $rows = array();
  while( $customItems = db_fetch_object($result) )
  {
    $row = array();
    $row[] = $customItems->url; 
    $row[] = $customItems->title;
    $row[] = $customItems->redirect;
    $row[] = l(t('edit'), 
              'admin/build/baker/edit/'. $customItems->bid, 
              array( 'attributes' => array('class' => 'popups-form'))
              ) .', '. l(t('delete'), 
                        'admin/build/baker/delete/'. $customItems->bid);
    $rows[] = $row;
  }  
  $output =  theme('table',$header,$rows);
  return $output;
}

function _baker_popups_links(){
  popups_add_popups();
  $output =  l("Add new title", 'admin/build/baker/add',
               array( 'attributes' => array('class' => 'popups-form')));
  return $output;

}
/**
 * Validate and prepare the user inputs to be inserted
 *
 * @return void
 * @author fran
 **/
function baker_admin_form_validate($form, &$form_state)
{
  //TODO:
}

function baker_admin_form_submit($form, &$form_state) {
  //register user input customization.
  $customItem = (object)$form_state['values'];
  _baker_save_custom_bread($customItem);
  //$form_state['redirect'] = 'admin/build/baker';
}

/**
 * Save the user input from administration panel
 *
 * @return void
 * @author fran
 **/
function _baker_save_custom_bread($customItem = null) 
{ 
  //edit case.
  if (isset($customItem->bid)) {
    drupal_write_record('baker', $customItem, 'bid');
  }
  else {
    drupal_write_record('baker', $customItem);
  }
}

/**
 * undocumented function
 *
 * @return void
 * @author fran
 **/
function _baker_delete_item()
{
  $bid = arg(4);
  
  $sql = "delete from baker where bid = %d";
  db_query($sql, $bid);
  
}


/**
 * Get the bid row information  
 *
 * @return $customItem
 * @author fran
 **/
function _baker_get_custom_breadcrumb($bid)
{
  $sql = "select * from baker where bid = %d";
  $result = db_query($sql, $bid);
  $customItem = db_fetch_object($result);
  return $customItem;
}