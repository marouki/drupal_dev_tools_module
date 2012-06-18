<?php
/**
 * @desc make Short Link
 * @author amine.cherif
 * @var unknown_type
 */
define('bitlyUser', variable_get('bitlyUser','o_453rm9k7b2'));
define('bitlyApiKey', variable_get('bitlyApiKey','R_e0d8e60be54aa9eaffb52f760d64e96b'));
/* make a URL small */
function make_bitly_url($url, $login = bitlyUser, $appkey = bitlyApiKey,
		$format = 'xml', $version = '2.0.1') {
	//create the URL
	$bitly = 'http://api.bit.ly/shorten?version=' . $version . '&longUrl='
			. urlencode(trim($url)) . '&login=' . $login . '&apiKey=' . $appkey
			. '&format=' . $format;

	//get the url
	//could also use cURL here
	$response = file_get_contents($bitly);

	//parse depending on desired format
	if (strtolower($format) == 'json') {
		$json = @json_decode($response, true);
		return $json['results'][trim($url)]['shortUrl'];
	} else //xml
	{
		$xml = simplexml_load_string($response);
		return 'http://bit.ly/' . $xml->results->nodeKeyVal->hash;
	}
}

/**
 * @desc make a link from char matched as an URL
 * @author amine.cherif
 * @var unknown_type
 */
function _make_url_clickable_cb($matches) {
	$ret = '';
	$url = $matches[2];

	if (empty($url))
		return $matches[0];
	// removed trailing [.,;:] from URL
	if (in_array(substr($url, -1), array('.', ',', ';', ':')) === true) {
		$ret = substr($url, -1);
		$url = substr($url, 0, strlen($url) - 1);
	}
	return $matches[1]
	. "&nbsp;<a href=\"$url\" target='_blank'>$url</a>&nbsp;&nbsp;"
	. $ret;
}
	/**
	* @desc make a link from char matched as an FTP URL
	* @author amine.cherif
	* @var unknown_type
	*/
	function _make_web_ftp_clickable_cb($matches) {
	$ret = '';
	$dest = $matches[2];
	$dest = 'http://' . $dest;

	if (empty($dest))
		return $matches[0];
		// removed trailing [,;:] from URL
		if (in_array(substr($dest, -1), array('.', ',', ';', ':')) === true) {
			$ret = substr($dest, -1);
			$dest = substr($dest, 0, strlen($dest) - 1);
		}
		return $matches[1] . "<a href=\"$dest\" rel=\"nofollow\">$dest</a>" . $ret;
	}
	/**
	 * @desc make a mailto link from char matched as an email
	 * @author amine.cherif
	 * @var unknown_type
	 */
	function _make_email_clickable_cb($matches) {
		$email = $matches[2] . '@' . $matches[3];
		return $matches[1] . "<a href=\"mailto:$email\">$email</a>";
	}
	/**
	 * @desc make a link from char matched as an URL OR MAIL OR FTP
	 * @author amine.cherif
	 * @var unknown_type
	 */
	function make_clickable($ret) {
		$ret = ' ' . $ret;
		// in testing, using arrays here was found to be faster
		$ret = preg_replace_callback(
				'#([\s>])([\w]+?://[\w\\x80-\\xff\#$%&~/.\-;:=,?@\[\]+]*)#is',
				'_make_url_clickable_cb', $ret);
		$ret = preg_replace_callback(
				'#([\s>])((www|ftp)\.[\w\\x80-\\xff\#$%&~/.\-;:=,?@\[\]+]*)#is',
				'_make_web_ftp_clickable_cb', $ret);
		$ret = preg_replace_callback(
				'#([\s>])([.0-9a-z_+-]+)@(([0-9a-z-]+\.)+[0-9a-z]{2,})#i',
				'_make_email_clickable_cb', $ret);

		// this one is not in an array because we need it to run last, for cleanup of accidental links within links
		$ret = preg_replace("#(<a( [^>]+?>|>))<a [^>]+?>([^>]+?)</a></a>#i",
				"$1$3</a>", $ret);
		$ret = trim($ret);
		return $ret;
	}
	/**
	 * @desc parse XML FILE
	 * @author amine.cherif
	 * @var unknown_type
	 */
	function parseXML($url) {
		return simplexml_load_file($url);
	}

	/**
	 * Recherche une valeur dans un tableau multi dimension
	 *
	 * {@source }
	 * @param string $needle Respecte la casse
	 * @param array $haystack Tableau multi dimension
	 * @param array $nodes[optional]
	 * @return array
	 */
	function multidimArraySearch($needle, $haystack, $nodes = '') {

		if (is_array($haystack)) {

			foreach ($haystack as $key1 => $value1) {

				if (is_array($value1)) {

					$nodes = multidimArraySearch($needle, $value1, $nodes);

				} elseif ($value1 == $needle) {

					$nodes = array($key1 => $value1);

				}

			}

		} else {

			$nodes = '';

		}

		return $nodes;

	}

	/**
	 * Fonction de DÃ©bug affichage au niveau de firebug.
	 *
	 * Valeurs prises par type
	 * FirePHP::LOG
	 * FirePHP::INFO
	 * FirePHP::WARN
	 * FirePHP::ERROR
	 * FirePHP::DUMP
	 *
	 * {@source }
	 *
	 * @param object $var
	 * @param Sting $msg
	 * @param String $type
	 * @return String $var
	 *
	 */

	function printDebug($var, $msg, $type) {

		eval('fb($var, $msg , FirePHP::' . strtoupper($type) . ');');
	}

	/**
	 * Fait un trim Ã  chaque valeur du tableau
	 * @return array
	 * @param array $tab
	 */
	function trimArray($tab) {
		foreach ($tab as $key => $value) {
			$tab[$key] = trim($value);
		}

		return $tab;
	}

	/**
	 * enleve les accent d'une chaine
	 * @return string
	 * @param $string string
	 */
	function dropAccent($string) {
		//$string = utf8_encode($string);
		$accent = str_split("Ã€Ã�Ã‚ÃƒÃ„Ã…Ã Ã¡Ã¢Ã£Ã¤Ã¥Ã’Ã“Ã”Ã•Ã–Ã˜Ã²Ã³Ã´ÃµÃ¶Ã¸ÃˆÃ‰ÃŠÃ‹Ã¨Ã©ÃªÃ«Ã‡Ã§ÃŒÃ�ÃŽÃ�Ã¬Ã­Ã®Ã¯Ã™ÃšÃ›ÃœÃ¹ÃºÃ»Ã¼Ã¿Ã‘Ã±");
		$sansAccent = str_split(
				"aaaaaaaaaaaaooooooooooooeeeeeeeecciiiiiiiiuuuuuuuuynn");

		$string = str_replace($accent, $sansAccent, utf8_decode($string));

		return $string;
	}
	/**
	 * enleve les espaces d'une chaine
	 * @return string
	 * @param $string string
	 */
	function enleveEspace($string) {
		return str_replace(" ", "", $string);
	}

	/**
	 * Affiche un tableau sous forme d'une liste
	 * Utilisation pour dÃ©veloppement (lisibilitÃ©)
	 *
	 * {@source }
	 * @param void
	 *
	 * @return array
	 */
	function affTab($tab) {
		if (is_array($tab)) {
			print "<ul>";
			foreach ($tab as $cle => $val) {
				$nb = count($val);
				if (!is_array($val)) {
					print "<li>$cle => $val\n<br>";
				} else {
					print "<li>$cle ($nb enfants) \n<br>";
					affTab($val);
			}
		}
		print "</ul>";
	} else {
		print_r($tab);
	}
}

/**
* Fusionne les tableaux $_POST & $_GET
* Ajoute aussi le login de l'utilisateur
*
* {@source }
*
* @return array
*/
function getParams() {

	$rValue = array();
	$rValue = array_merge($_POST, $_GET);

	return $rValue;
}

/**
 * Ajout Ã  un tableau les cellules "success", "totalCount" et "errorMessage"
 *
 * {@source }
 *
 * @param array $tab
 * @param string $key : dÃ©signe le clÃ© de la cellule des valeurs
 * @param boolean $forceSuccess[optional] : force success Ã  true mÃªme si $tab et vide
 * @param $msg[optional] : message Ã  afficher en cas d'erreur
 * @param $totalCount[optional] : le nombre total Ã  retourner
 * @return array
 */
function formatArray($tab, $key, $forceSuccess = false, $msg = '', $totalCount = 0) {

	$rValue = array();

	// totalCount
	if ($totalCount) {

		$lenght = $totalCount;

	} elseif (is_array($tab)) {

		$lenght = count($tab);

	} else {

		$lenght = 0;

	}

	if ($lenght > 0 || $forceSuccess == true) {// Success

		$rValue['success'] = true;
		$rValue['totalCount'] = $lenght;
		$rValue['errorMessage'] = '';
		$rValue[$key] = $tab;

	} else {// Failer

		$rValue['success'] = false;
		$rValue['totalCount'] = 0;

		if ($msg) {
			$rValue['errorMessage'] = $msg;
		} else {
			$rValue['errorMessage'] = 'Erreur!';
		}

		$rValue[$key] = array();

	}

	//ajout de la date d'operation
	$rValue["dateOperation"] = date("F d, Y");

	return $rValue;
}

/**
 * Extraire les donnÃ©es utiles pour la mise Ã  jour ou l'insertion dans la BD
 * Pour mettre la valeur null Ã  un champ, il faut envoyer la valeur "unset" dans la cellule du tableau $params
 *
 * {@source }
 *
 * @param Object $object
 * @param array $params
 *
 *  @return array
 */
function extractData($object, $params) {

	$data = array();

	foreach ($object as $key => $val) {
		if ((isset($params[$key])) && (strpos($key, '_') != 1)) {

			if ($params[$key] == "unset") {
				$params[$key] = null;
			}
			$data[$key] = $params[$key];
		}
	}

	return encodeKeysToDB($data);
}

/**
 * Formate les keys d'un tableau pour la Base de donnÃ©es
 *
 * {@source }
 *
 * @param array $params
 *
 * @return array
 */
function encodeKeysToDB($tab) {
	$rValue = array();

	foreach ($tab as $key => $val) {
		$rValue[strFormatingToDb($key)] = $tab[$key];
	}

	return $rValue;
}

/**
 * Formate les keys d'un tableau pour le JavaScript
 *
 * {@source }
 *
 * @param array $params
 *
 * @return array
 */
function encodeKeysToJs($tab) {

	$rValue = array();

	if (is_array($tab)) {
		foreach ($tab as $key => $val) {
			if (is_array($val)) {
				$rValue[strFormatingFromDB($key)] = encodeKeysToJS($val);
			} else {
				$rValue[strFormatingFromDB($key)] = $val;
			}
		}
	}

	return $rValue;
}

/**
 * Remplace les caractÃ©res majuscule en '_'.caractÃ©re minuscule
 *
 * {@source }
 *
 * @param string $chaine
 *
 * @return string
 */
function strFormatingToDb($chaine) {

	for ($i = 0; $i < strlen($chaine); $i++) {

		$char = substr($chaine, $i, 1);
		$dec = ord($char);

		if (($dec >= 65) && ($dec <= 90)) {
			$chaine = substr_replace($chaine, '_' . strtolower($char), $i, 1);
		}

	}

	return $chaine;

}

/**
 * Remplace  les caractÃ©res '_'.caractÃ©re minuscule en majuscule
 *
 * {@source }
 *
 * @param string $chaine
 *
 * @return string
 */
function strFormatingFromDB($chaine) {

	$charac = '';
	$rValue = '';
	$chaine = (string) $chaine;

	for ($i = 0; $i < strlen($chaine); $i++) {
		$charac = $chaine{$i};
		if ($charac == '_') {
			$characReplace = strtoupper($chaine{$i + 1});
			$i = $i + 1;
		} else {
			$characReplace = $charac;
		}
		$rValue .= $characReplace;

	}

	return $rValue;
}

/**
 * Encodage des donnÃ©es suivant la notation demandÃ©e
 *
 * {@source }
 * @param string $notation Type d'encodage (json, xml, ...)
 * @param array $data DonnÃ©es Ã  encoder
 * @param string $fileName[optional] : nom du fichier pour le cas de l'export csv.
 *
 * @return void
 */
function encodeData($notation, $data, $fileName = '') {
	switch ($notation) {
		case 'json':
			foreach ($data as $key => $value) {
				$data[$key] = str_replace("\n", "", $value);
				$data[$key] = str_replace("\r", "", $value);
			}
			print json::encode($data);
			break;

		case 'csv':
			header("Content-Type: application/x-msexcel");
			header("Content-disposition: filename=$fileName.xls");
			$rValue = exportCsv($data);
			print $rValue;
			break;

		default:
			print $data;
			break;
	}

}

/**
 * DÃ©codage des donnÃ©es suivant la notation demandÃ©e
 *
 * {@source }
 * @param string $notation
 * @param array $data
 *
 * @return void
 */
function decodeData($notation, $data, $toDecode = "") {

	switch ($notation) {
		case 'json':
			return json::decode($data);
			break;

		case 'nextedia':
			return nexTransform($data, $toDecode);
			break;

		default:
			print 'Type de decodage non defini';
			break;
	}

}

function nexTransform($data, $todecode) {

	$todecode = $data[$todecode];
	$todecode = str_replace("{", " ", $todecode);
	$todecode = str_replace("}", " ", $todecode);
	$todecode = str_replace(":", "=", $todecode);

	$ligne = explode(",", $todecode);

	$ligne2 = array();
	foreach ($ligne as $key => $value) {

		$op = strpos($value, "=");
		$rdata = substr($value, 0, $op);
		$ldata = substr($value, $op + 1, strlen($value) - $op);

		$rdata = trim(str_replace("\"", "", $rdata));
		$ldata = trim($ldata);
		$ldata = substr($ldata, 1, strlen($ldata) - 2);
		$ligne2[$rdata] = $ldata;
	}

	//print_r($ligne2);

	$data = array_merge($data, $ligne2);

	return $data;

}

function ndata($champ, &$maligne) {
	$mid = $maligne;
	$mid = str_replace("\"", "", $mid);
	$mid = str_replace("$champ=", "", $mid);// Ã  enlever pour que le nom du champ reste
	$mid = trim($mid);
	return $mid;
}

/**
 * Formatage des donnÃ©es d'un tableau pour l'export CSV
 *
 * @param array $tab
 *
 * @return string
 * @author sguerbaa
 * j'ai ajoutÃ© le utf8_decode par defaut sur cette fonction pour aviter le parcour du tableau de foix
 * une avant passage a la fonction et l'autre dans la fonction
 */
function exportCsv($tab) {

	$csvTerminated = "\n";
	$csvSeparator = "\t";
	$csvEnclosed = '"';
	$csvEscaped = '""';

	foreach ($tab['titles'] as $v) {
		$header .= utf8_decode($v) . $csvSeparator;
	}

	for ($i = 0; $i < count($tab['values']); $i++) {
		$line = '';
		foreach ($tab['values'][$i] as $v) {
			if ($v != '') {
				$v = $csvEnclosed
				. str_replace($csvEnclosed, $csvEscaped,
						utf8_decode(trim($v))) . $csvEnclosed
						. $csvSeparator;
			} else {
				$v = $csvEnclosed . $csvEnclosed . $csvSeparator;
			}
			$line .= $v;
		}

		$rValue .= trim($line) . $csvTerminated;
	}

	$rValue = str_replace("\r", "", $rValue);

	if ($rValue == "") {
		$rValue = utf8_decode("\n(0) Enregistrements trouvÃ©s!\n");
	}

	return $header . $csvTerminated . $rValue;

}

/**
 * Rassemble les Ã©lÃ©ments d'un tableau en une chaÃ®ne
 * sous la forme key = value AND key1= value1...
 *
 * {@source }
 *
 * @param string $prefixe
 * @param string $table
 * @param array $data
 *
 * @return string $chaine
 * @author garboo3
 * j'ai ajoutÃ© un addslaches pour ecorriger les bug liÃ©e au accents
 */
function immplodeForDB($prefixe, $table, $data) {
	$chaine = "";
	$tab = array();

	if (is_array($data)) {
		foreach ($data as $key => $value) {
			$value = addslashes($value);
			$chaine .= " AND $prefixe$table.$key  = '$value' ";
		}
	}

	return $chaine;
}

/**
 * CrÃ©ation de fichier a partir d'un upload
 *
 *
 * @param $dir Object
 * @param $name Object[optional]
 *
 * @return boolean
 */
function moveUploadedFile($dir, $name = "") {

	/**
	 * verification del'existence du dossier sinon le creer, si c impossible
	 * l'execution s'arrete et la methode retourne false
	 *
	 */

	if (!is_dir($dir)) {
		if (!mkdir($dir))
			return false;
	} /*else {
	try{
	chmod($dir,0777);
	}
	catch (Exception $e){
	continue;
	}
	}*/

	if (count($_FILES)) {
		foreach ($_FILES as $key => $value) {

			if (!$name) {
				$name = $value["name"];
			}

			if (!copy($value["tmp_name"], $dir . $name)) {
				return false;
			} /*else{
			unlink($dir.$name);
			}*/
		}
	}

	return true;
}
/**
 * enlever toutes les case vide d'un tableau
 *
 * @param array $tab
 *
 * @return array $tab
 */
function enleveCaseVide($tab) {
	foreach ($tab as $key => $value) {
		if (!$value)
			unset($tab[$key]);
	}
	return $tab;
}

/**
 * enlever toutes les guillumet inutile gÃ©nÃ©rÃ© par un export
 *
 * @param string $chaine
 *
 * @return string $chaine
 * @author sguerbaa
 */
function enleveGuillemet($chaine) {
	$long = strlen($chaine);
	$chaine2 = $chaine;
	if (strpos($chaine, '"') === 0)
		$chaine2 = substr($chaine, 1);
	if (strrpos($chaine, '"') === $long - 1)
		$chaine2 = substr($chaine2, 0, $long - 2);
	$chaine2 = ereg_replace('""', '"', $chaine2);
	return $chaine2;
}

/**
 * enlever toutes les guillumet inutile gÃ©nÃ©rÃ© par un export d'un tableau
 *
 * @param array $tab
 *
 * @return array $tab
 * @author sguerbaa
 */
function arrayEnleveGuillemet($tab) {
	if (is_array($tab)) {
		foreach ($tab as $key => $value) {
			$tab[$key] = enleveGuillemet($value);
		}
	}

	return $tab;
}

/**
 * fonction qui compare deux tableau recursivement
 * @return $resultArray array
 * @param $arrayA array
 * @param $arrayB array
 */
function compareArray($arrayA, $arrayB) {
	$resultArray = array();
	foreach ($arrayA as $key => $value) {
		if (is_array($value)) {
			$resultArray[$key] = compareArray($arrayA[$key], $arrayB[$key]);
		}
		else {
			if ($arrayA[$key] !== $arrayB[$key]) {
				$resultArray[$key]["newValue"] = $arrayA[$key];
				$resultArray[$key]["originalValue"] = $arrayB[$key];
			}
		}
	}
	return $resultArray;
}
/* nettoyage des IDs de la form [\"id1\",\"id2\"] return une chaine id1,id2 */

function cleanIds($var) {
	$machaine = $var;
	$cl = str_replace('[', "", $machaine);
	$cl = str_replace(']', "", $cl);
	$cl = str_replace('"', "'", $cl);
	return $cl;
}
//get all node types
list($_node_types, $_node_names) = _node_types_build();
global $allCt;
$allCt = array_keys($_node_names);

