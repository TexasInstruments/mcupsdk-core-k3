/* MIT License

* Copyright (c) 2016 Robin Lobel
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

var searchResultsText=["Sorry, no documents matching your query.","Found <b>1</b> document matching your query.","Found <b>$num</b> documents matching your query."];
var serverUrl="file://C:/SL/DOC TOOLS/SLP DOCOUT/searchengine.html";
var tagMap = {
};

function SearchBox(name, resultsPath, inFrame, label)
{
  this.searchLabel = label;
  this.DOMSearchField = function()
  {  return document.getElementById("MSearchField");  }
  this.DOMSearchBox = function()
  {  return document.getElementById("MSearchBox");  }
  this.OnSearchFieldFocus = function(isActive)
  {
    if (isActive)
    {
      this.DOMSearchBox().className = 'MSearchBoxActive';
      var searchField = this.DOMSearchField();
      if (searchField.value == this.searchLabel)
      {
        searchField.value = '';
      }
    }
    else
    {
      this.DOMSearchBox().className = 'MSearchBoxInactive';
      this.DOMSearchField().value   = this.searchLabel;
    }
  }
}

function trim(s) {
  return s?s.replace(/^\s\s*/, '').replace(/\s\s*$/, ''):'';
}

function getURLParameter(name) {
  return decodeURIComponent((new RegExp('[?|&]'+name+
         '='+'([^&;]+?)(&|#|;|$)').exec(location.search)
         ||[,""])[1].replace(/\+/g, '%20'))||null;
}

var entityMap = {
  "&": "&amp;",
  "<": "&lt;",
  ">": "&gt;",
  '"': '&quot;',
  "'": '&#39;',
  "/": '&#x2F;'
};

function escapeHtml(s) {
  return String(s).replace(/[&<>"'\/]/g, function (s) {
    return entityMap[s];
  });
}

function escapeRegExp(s) {
  return String(s).replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
}

function normalizeSearchText(s) {
  return String(s || "")
    .toLowerCase()
    .replace(/[^a-z0-9]+/g, ' ')
    .replace(/\s+/g, ' ')
    .trim();
}

function highlightTerms(text, terms) {
  var out = escapeHtml(text || "");
  var hlOpen = '<span class="hl" style="background-color:#ffeb3b;color:#111;font-weight:700;padding:0 2px;border-radius:2px;">';
  var hlClose = '</span>';
  for (var i = 0; i < terms.length; i++) {
    var re = new RegExp('(' + escapeRegExp(terms[i]) + ')', 'ig');
    out = out.replace(re, hlOpen + '$1' + hlClose);
  }
  return out;
}

function searchFor(query,page,count) {
  var normalizedQuery = trim(query);
  var queryLc = normalizeSearchText(normalizedQuery);
  var terms = queryLc.split(/\s+/).filter(function(t) { return t.length >= 2; });

  if(terms.length===0)
    {
        var results = $('#searchresults');
    results.html('<p>Query too short (2 chars minimum per term).</p>');
        return;
    }

    var xmlData=document.getElementById('searchdata').innerHTML;
    if(xmlData.indexOf("<add>")<0)
    {
        alert("Append <script id=\"searchdata\" type=\"text/xmldata\"> to the content of search.html, then the content of searchdata.xml, and end by </script>.\n\nsearchdata.xml is generated when SEARCHENGINE, SERVER_BASED_SEARCH and EXTERNAL_SEARCH options are enabled.");
        return;
    }
    xmlData=xmlData.substring(xmlData.indexOf("<add>"),xmlData.indexOf("</add>")+6);

    var xmlParser=new DOMParser().parseFromString(xmlData,"text/xml");

  var matches=[];
  var partialMatches=[];
    var doc=xmlParser.getElementsByTagName("doc");
    for (i=0;i<doc.length;i++)
    {
        var fields = doc[i].getElementsByTagName("field");
        if (fields.length < 3) continue;

        type = (fields[0].childNodes.length > 0) ? fields[0].childNodes[0].nodeValue : "";
        name = (fields[1].childNodes.length > 0) ? fields[1].childNodes[0].nodeValue : "";
        url  = (fields[2].childNodes.length > 0) ? fields[2].childNodes[0].nodeValue : "";

        if (fields.length < 4 || fields[3].childNodes.length==0)
          heading = ""
        else
          heading=fields[3].childNodes[0].nodeValue;
        if (fields.length < 5 || fields[4].childNodes.length==0)
          text = ""
        else
          text=fields[4].childNodes[0].nodeValue;

        var allFieldText = "";
        for (var fi = 0; fi < fields.length; fi++)
        {
          if (fields[fi].childNodes.length > 0)
          {
            allFieldText += " " + fields[fi].childNodes[0].nodeValue;
          }
        }

        var typeLc = normalizeSearchText(type);
        var nameLc = normalizeSearchText(name);
        var headingLc = normalizeSearchText(heading);
        var urlLc = normalizeSearchText(url);
        var textLc = normalizeSearchText(text);
        var allFieldTextLc = normalizeSearchText(allFieldText);
        var searchable = allFieldTextLc + " " + urlLc;

        var allTermsFound = true;
        var matchedTerms = 0;
        var score = 0;
        for (var t=0; t<terms.length; t++)
        {
          var term = terms[t];
          if(searchable.indexOf(term)<0)
          {
            allTermsFound = false;
            continue;
          }

          matchedTerms++;

          if(nameLc === term) score += 100;
          else if(nameLc.indexOf(term)===0) score += 60;
          else if(nameLc.indexOf(term)>=0) score += 40;

          if(headingLc === term) score += 90;
          else if(headingLc.indexOf(term)===0) score += 50;
          else if(headingLc.indexOf(term)>=0) score += 30;

          if(typeLc.indexOf(term)>=0) score += 10;

          if(urlLc.indexOf(term)>=0) score += 10;

          var textPos = textLc.indexOf(term);
          if(textPos>=0)
          {
            score += 20;
            var nextPos = textPos;
            while(nextPos>=0)
            {
              score += 1;
              nextPos = textLc.indexOf(term, nextPos + term.length);
            }
          }
        }

        if(allTermsFound)
        {
          if (searchable.indexOf(queryLc) >= 0) score += 80;

          matches.push({
            type:type,
            name:name,
            heading:heading,
            url:url,
            text:text,
            allText:allFieldText,
            score:score
          });
        }
        else if (matchedTerms > 0)
        {
          var partialScore = score + (matchedTerms * 15) - 50;
          partialMatches.push({
            type:type,
            name:name,
            heading:heading,
            url:url,
            text:text,
            allText:allFieldText,
            score:partialScore
          });
        }
    }

      if(matches.length===0)
      {
        matches = partialMatches;
      }

      matches.sort(function(a,b){ return b.score-a.score; });

      count=matches.length;
      output='<table>';
      for (var m=0; m<matches.length; m++)
      {
        var item = matches[m];
        var typeEsc = highlightTerms(item.type, terms);
        var nameEsc = highlightTerms(item.name, terms);
        output+='<tr class="searchresult">';
        output+='<td align="right">'+(m+1)+'.</td>';
        output+='<td>'+typeEsc+'&#160;';
        output+='<a href="'+escapeHtml(item.url)+'">';
        output+=nameEsc;
        output+='</a>';
        output+='</td>';

        if(item.heading)
        {
          var headingEsc = highlightTerms(item.heading, terms);
          output+='<tr><td></td><td><strong>'+headingEsc+'</strong></td></tr>';
        }

        var snippetSource = item.text ? item.text : (item.heading ? item.heading : item.allText);
        var textLc = snippetSource.toLowerCase();
        var fragmentcount=0;
        var usedStarts = {};

        for (var ti=0; ti<terms.length && fragmentcount<3; ti++)
        {
          var term = terms[ti];
          var start=textLc.indexOf(term);
          if(start<0) continue;

          if(usedStarts[start]) continue;
          usedStarts[start] = true;

          var quotestart=Math.max(start-40,0);
          var quoteend=Math.min(start+term.length+40,snippetSource.length);
          var fragment='';
          if(quotestart>0)
            fragment+='...';

          var segment = snippetSource.substring(quotestart,quoteend);
          var segmentEsc = highlightTerms(segment, terms);
          fragment+=segmentEsc;

          if(quoteend<snippetSource.length)
            fragment+='...';
          output+='<tr><td></td><td>'+fragment+'</td></tr>';
          fragmentcount++;
        }

        output+="</tr>";
      }
    output+="</table>";
    var results = $('#searchresults');
    if (count==0) {
        results.html('<p>'+searchResultsText[0]+'</p>');
    } else if (count==1) {
        results.html('<p>'+searchResultsText[1]+'</p>');
    } else {
        results.html('<p>'+searchResultsText[2].replace(/\$num/,count)+'</p>');
    }
    results.append(output);
}

$(document).ready(function() {
  var query = trim(getURLParameter('query'));
  if (query) {
    searchFor(query,0,20);
  } else {
    var results = $('#searchresults');
    results.html('<p>Sorry, no documents matching your query.</p>');
  }
});
