/**
 * @author amine.cherif
 * @desc commun js functions & tools
 */

/**
 * @author hajer.ghorbal
 * @param form_id
 * @param email
 * @return boolean
 * @desc verification d'un champ email
 */
function verif_mail_newsletter(form_id, email) {
	var reg = /^([A-Za-z0-9_\-\.])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$/;
	email = $('#'+form_id).val();
	if (reg.test(email) == false || email == "") {
		return (false);
	} else {
		return true;
	}
}
/**
 * COOKIES MANAGER
 * @desc set cookie
 * @param name
 * @param vall
 * @return
 */
function set_cookie(name, vall) {
	$.cookie(name, val, { path: "/", expires: 1  });
	}
/**
 * COOKIES MANAGER
 * @desc get cookie
 * @param name
 * @param vall
 * @return
 */
function read_cookie(name) {
	return  $.cookie(name);
}

/**
 * @desc AJout au favoris
 * @author macherif
 * @date 27/01/2012
 */
function bookmark() {
	bookmarkurl = location.href;
	bookmarktitle = document.title;
	if (document.all) { 
		window.external.AddFavorite(bookmarkurl, bookmarktitle);
	} else if (window.sidebar) { // firefox
		window.sidebar.addPanel(bookmarktitle, bookmarkurl, "");
	} else if (window.opera && window.print) { // opera
		var elem = document.createElement('a');
		elem.setAttribute('href', url);
		elem.setAttribute('title', title);
		elem.setAttribute('rel', 'sidebar');
		elem.click();
	} else {
		 alert('Appuyez sur CTRL + D pour ajouter cette page à vos Favoris');
		/*chrome.bookmarks.create( {
			'parentId' : bookmarkBar.id,
			'title' : bookmarktitle,
			'url' : bookmarkurl
		}, function(newFolder) {
			console.log("added folder: " + newFolder.title);
		});*/
	}
}

/**
 * @function getShare
 * @desc build FB share event
 */
function displayFBUI(title, linkAttach, imgAttach, desc) {
	FB.ui(
			  {
			    method: 'feed',
			    name: title,
			    link: linkAttach,
			    picture: imgAttach,
			    caption: title,
			    description: desc
			  },
			  function(response) {
			    if (response && response.post_id) {
			      //alert('Post was published.');
			    } else {
			      //alert('Post was not published.');
			    }
			  }
			);
}
/**
 * @desc open FB popoup for sharing
 * @param title
 * @param desc
 * @param url
 * @param picUrl
 * @param app_data
 * @returns
 */
function getShare(title,desc,url,picUrl,app_data){
	title = encodeURI(title);
	desc = encodeURI(desc);
	link = encodeURI(url+app_data); alert(link);
	picUrl = encodeURI(picUrl);
	return window.open("https://www.facebook.com/sharer.php?s=100&p[title]="+title+"&p[images][0]="+picUrl+"&p[summary]="+desc+"&p[url]="+link,"share","height=400, width=500, top=100, left=100, toolbar=no, menubar=yes, location=no, resizable=yes, scrollbars=no, status=no");
}
/**
 * @desc retourne la distance entre le top et l'element selectionné
 * @param divID
 * @returns char
 */
function get_from_top_to_div_length(divID){
	targetDivY = $('#'+divID).position().top;
	return targetDivY;
}

/**
 * @author naoufel
 * @desc suppression animée d'un élément du DOM
 */
function delete_object(selector)
{
        $(selector).css({
                'background': '#ff8888 !important',
                'color': '#941010'
        }).fadeOut(500, function() {
                $(this).remove();
        });
}
//cookie create
function setCookieSimple(c_name,value,expiredays) {
	var exdate=new Date();
	exdate.setDate(exdate.getDate()+expiredays);
	document.cookie=c_name+ "=" +escape(value)+((expiredays==null) ? "" : ";expires="+exdate.toGMTString());
	}
// cookie retrieve
function getCookieSimple(c_name) {
	if (document.cookie.length>0) {
	c_start=document.cookie.indexOf(c_name + "=");
	if (c_start!=-1) { 
	c_start=c_start + c_name.length+1;
	c_end=document.cookie.indexOf(";",c_start);
	if (c_end==-1) c_end=document.cookie.length;
	return unescape(document.cookie.substring(c_start,c_end));
	}
	}
	return "";
}

/**
 * Encode un URL à un objet
 * 
 * @param {String} string
 * @param {Boolean} asArray (optional), regroupement des valeurs d'une même variable dans un array exp:{ foo: 1, bar: ['bleck', 'gah', 'meh'] };
 * 
 * @return {object}
 */
function paramsDecode(string, asArray){
    if(!string || !string.length){
        return {};
    }
    var obj = {};
    var pairs = string.split('&');
    var pair, name, value;
    for(var i = 0; i < pairs.length; i++){
        pair = pairs[i].split('=');
        name = pair[0];
        value = pair[1];
        if(asArray){
            if(typeof obj[name] == "undefined"){
                obj[name] = value;
            }else if(typeof obj[name] == "string"){
                obj[name] = [obj[name]];
                obj[name].push(value);
            }else{
                obj[name].push(value);
            }
        }else{
            obj[name] = decodeEtCommercial(value);
        }
    }
    return obj;
}

/**
 * 
 * @param {string} value
 * 
 * @return {string} rValue
 */
function decodeEtCommercial(value) {
    return value.replace(/%26/g, '&');
}

/**
 * 
 * @param {string} stringToTrim
 */
function trim(stringToTrim) {
    return stringToTrim.replace(/^\s+|\s+$/g,"");
}

/**
 * Mettre la première lettre en majuscule
 * 
 * @param {string} chaine
 * 
 * @return {string} rValue
 */
function ucFirst(chaine) {
    var i;
    var charac;
    var rValue = '';

	for (i = 0; i < chaine.length; i++) {			
		charac = chaine.charAt(i);
		if(i==0) {
			charac = charac.toUpperCase(charac)
		}
		rValue = rValue + charac;
	}
	return rValue;
}

/**
 * 
 * @param {string} chaine
 * 
 * @return {string} rValue
 */
function removeAccent(chaine) {
    rValue = chaine.replace(/[àáâãäå]/gi,"a");
    rValue = rValue.replace(/[éèêë]/gi,"e");
    rValue = rValue.replace(/[ìíîï]/gi,"i");
    rValue = rValue.replace(/[òóôõöø]/gi,"o");
    rValue = rValue.replace(/[ùúûü]/gi,"u");
    rValue = rValue.replace(/[ç]/gi,"c");
    return rValue;
}

/**
 * 
 * @param {string} chaine
 * 
 * @return {string} rValue
 */
function generateId(chaine) {
    var i;
    var j = 1;
    var charac;
    var rValue = '';
    chaine = removeAccent(chaine);
    chaine = chaine.replace(/[^a-z0-9_\s]/gi,'');
    chaine = chaine.toLowerCase(chaine);
    
    for (i = 0; i < chaine.length; i++) {
        charac = chaine.charAt(i);
        if(charac == ' ') {
            characReplace = '_';
        } else {                    
            if (j <= 45) {
                characReplace = charac;
            } else {
                characReplace = '';
            }
            j = j + 1;
        }
        rValue = rValue + characReplace;
    }
    
    return rValue;                
}


