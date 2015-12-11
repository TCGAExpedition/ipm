<?php
/**
 * The PGRR portal is a resource for sharing genomic data in a resource community.
 * Copyright (C) 2015  University of Pittsburgh
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

// $Id: EntrezPubmedArticle.php 16574 2011-04-28 22:53:39Z pitt\sss53 $

/**
 * FaceBaseEntrezPubmedArticle 
 *
 * Provides a class for handling PubMed articles retrieved with EFetch.
 * Originally writen by Stefan Freudenberg
 * 
 * @package 
 * @version $id$
 */
class FaceBaseEntrezPubmedArticle
{
  /**
   * _article 
   * 
   * @var mixed
   * @access private
   */
  private $_article;

  /**
   * _id 
   * 
   * @var mixed
   * @access private
   */
  private $_id;

  /**
   * _md5 
   * 
   * @var mixed
   * @access private
   */
  private $_md5;

  /**
   * _fb_pub 
   * 
   * @var array
   * @access private
   */
  private $_fb_pub = array();

  /**
   * __construct 
   *
   * Stores the given SimpleXMLElement the PubMed ID and the md5 hash of the
   * serialized XML.
   * 
   * @param SimpleXMLElement $pubmedArticle 
   * @access public
   * @return void
   */
  public function __construct(SimpleXMLElement $pubmedArticle = NULL)
  {
    if ($pubmedArticle) {
      $this->setArticle($pubmedArticle);
    }
  }

  /**
   * setArticle 
   *
   * Returns the PubMed ID of the article.
   * 
   * @param SimpleXMLElement $pubmedArticle 
   * @access public
   * @return void
   */
  public function setArticle(SimpleXMLElement $pubmedArticle)
  {
    $this->_article = $pubmedArticle->MedlineCitation;
    $this->_id = (int)$pubmedArticle->MedlineCitation->PMID;
    $this->_md5 = md5($pubmedArticle->asXML());
  }

  /**
   * getId 
   * 
   * @access public
   * @return int
   */
  public function getId()
  {
    return $this->_id;
  }

  /**
   * getMd5 
   *
   * Returns the md5 hash of the serialized XML.
   * 
   * @access public
   * @return string
   */
  public function getMd5()
  {
    return $this->_md5;
  }

  public function getPubAsObject() {
    return (object)$this->getPub();
  }

  /**
   * getPub 
   *
   * Returns article elements as an associative array suitable for 
   * import into a fb_pub node.
   * 
   * @access public
   * @return array
   */
  public function getPub()
  {
    if (empty($this->_fb_pub)) {
    	
//     	$abstract = $this->_article->Article->Abstract->children();
//     	if(is_array($this->_article->Article->Abstract->AbstractText)){
//     		$article = implode('<br /> ', $this->_article->Article->Abstract->AbstractText);
//     	}else{
//     		$article = (string)$this->_article->Article->Abstract->AbstractText;
//     	}
    	
      $this->_fb_pub = array(
        'title' => (string)$this->_article->Article->ArticleTitle,
        'body' => (string)$this->_article->Article->Abstract->AbstractText,
        'field_publication_pmid' => $this->_id,

        'field_publication_authors' => $this->_contributors(),
        'field_publication_date' => $this->_date(),
        'field_publication_journal' => (string)$this->_article->Article->Journal->Title,
        'field_publication_volume' => (string)$this->_article->Article->Journal->JournalIssue->Volume,
        'field_publication_issue' => (string)$this->_article->Article->Journal->JournalIssue->Issue,
        'field_publication_pagination' => (string)$this->_article->Article->Pagination->MedlinePgn,
      );

      $doi = $this->_article->xpath('//ELocationID[@EIdType="doi"]/text()');
      if (!empty($doi)) {
        $this->_fb_pub['field_publication_doi'] = (string)$doi[0];
      }
    }

    return $this->_fb_pub;
  }

  /**
   * _contributors 
   * 
   * Returns the list of contributors for import obtained from the given
   * MedlineCitation element.
   *
   * @access private
   * @return array
   *   the contributors of the article
   */
  private function _contributors()
  {
//     $contributors = array();

    if (isset($this->_article->Article->AuthorList->Author)) {
      foreach ($this->_article->Article->AuthorList->Author as $author) {
        if (isset($author->CollectiveName)) {
          // corporate author
          $name = (string)$author->CollectiveName;
        } 
        else {
          //primary (human) author
          $lastname = (string)$author->LastName;
          if (isset($author->ForeName)) {
            $name = $lastname . ', ' . (string)$author->ForeName;
          } 
          elseif (isset($author->FirstName)) {
            $name = $lastname . ', ' . (string)$author->FirstName;
          } 
          elseif (isset($author->Initials)) {
            $name = $lastname . ', ' . (string)$author->Initials;
          }
        }
        //$contributors[] = array(
          //'last_name' => $lastname ? $lastname : '',
          //'formatted_name' => $name,
        //);
        $contributors[] = $name;
      }
    }

    return $contributors;
  }

  /**
   * _date 
   * 
   * Returns the publication date obtained from the given MedlineCitation's
   * PubDate element. See the reference documentation for possible values:
   * http://www.nlm.nih.gov/bsd/licensee/elements_descriptions.html#pubdate
   * According to the above source it always begins with a four digit year.
   *
   * @access private
   * @return string
   *   the publication date of the article
   */
  private function _date()
  {
    $pubDate = $this->_article->Article->Journal->JournalIssue->PubDate;

    $months = array_flip(array('Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec'));
    if (isset($pubDate->MedlineDate)) {
      $date_string = (string)$pubDate->MedlineDate;
      $pattern = '^(\d{4}).?('.implode('|',array_keys($months)).')?';

      preg_match("/$pattern/i", $date_string, $matches); 

      $year = $matches[1];
      $month = isset($matches[2]) ? $months[$matches[2]]+1 : 1;
      $day = 1; // hardcode this

      //dfb(getdate($timestamp));
    } 
    else {
      $date_string = implode(' ', (array)$pubDate);
      $year = (int)$pubDate->Year;
      $month = isset($pubDate->Month) ? $months[(string)$pubDate->Month]+1 : 1;
      $day = isset($pubDate->Day) ? (int)$pubDate->Day : 1;

      //$timestamp = strtotime($date_string);
    }

    $timestamp = mktime(0,0,0,$month,$day,$year);
    //dfb(getdate($timestamp));

    $date = array(
      'display' => $date_string,
      'data' => strftime('%Y-%m-%d', $timestamp), 
    );

    return $date;
  }

  /**
   * _keywords 
   * 
   * @access private
   * @return void
   */
  private function _keywords() {
    $keywords = array();
    if (isset($this->_article->MeshHeadingList->MeshHeading)) {
      foreach ($this->_article->MeshHeadingList->MeshHeading as $heading) {
        $keywords[] = (string)$heading->DescriptorName;
      }
    }
    return $keywords;
  }

  /**
   * _lang 
   * 
   * @access private
   * @return void
   */
  private function _lang() {
    if (isset($this->_article->Article->Language)) {
      return (string)$this->_article->Article->Language;
    }

  }
}
