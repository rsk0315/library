// window.addEventListener('load', function(){
'use strict';
$(function() {
    const unbundle = function () {
        $('#unbundled').each(function(index, element) {
            $(element).parent().next().show();
        });
        $('#bundled').each(function(index, element) {
            $(element).parent().next().hide();
        });
        $('.code-bundle-btn').each(function(index, element) {
            $(element).text("Bundle");
        });
    };
    const bundle = function () {
        $('#unbundled').each(function(index, element) {
            $(element).parent().next().hide();
        });
        $('#bundled').each(function(index, element) {
            $(element).parent().next().show();
        });
        $('.code-bundle-btn').each(function(index, element) {
            $(element).text("Unbundle");
        });
    };
    // bundle されたコードは最初は非表示に
    let is_bundled = false;
    unbundle();

    // ボタンを実装
    $('pre > code').each(function(index, element) {
        // $(element).parent().wrap('<div style="position: relative;"></div>');
        // $(element).parent().parent().append('<div class="code-btn code-copy-btn" title="Copied!">Copy</div>');
        // $(element).parent().parent().append('<button type="button" class="code-btn code-bundle-btn" title="Bundled!">Bundle</button>');

        $(element).attr({id: `code-${index}`});

        $(element).parent().parent().prepend(`<div class="div-btn-copy"><span class="btn-copy btn-pre" tabindex="0" data-toggle="tooltip" data-trigger="manual" title="Copied!" data-original-title="Copied!" data-target="code-${index}">Copy</span></div>`);
        $(element).parent().parent().prepend(`<div class="div-btn-copy"><span class="btn-bundle btn-pre code-bundle-btn" tabindex="0" data-target="code-${index}">Bundle</span></div>`);
    });

    // $('[data-toggle="tooltip"]').tooltip();
    $('.btn-copy').on('click',function(){
        // テキスト要素を選択＆クリップボードにコピー
        let range = document.createRange();
        let selected = $('#'+$(this).attr('data-target'))[0];
        window.getSelection().removeAllRanges();
        range.selectNode(selected);
        window.getSelection().addRange(range);
        document.execCommand('copy');
        window.getSelection().removeAllRanges();

        let this_ = this;
        $(this).showBalloon(
            // 空でもオプションを与えるとこわれる，なにこれ
            // {
            //     showAnimation: function(d, c) { this.fadeIn(d, c); },
            //     css: { fontSize: '70%' },
            //     minLifetime: 300,
            //     maxLifetime: 300,
            // }
        );
        setTimeout(function() { $(this_).hideBalloon(); }, 300);
    });

    $('.code-bundle-btn').on('click', function(){
        // bundle / unbundle の切り替え
        if (is_bundled) {
            unbundle();
        } else {
            bundle();
        }
        is_bundled = ! is_bundled;
    });

    // 最悪なんですが，ファイルを追加するのが面倒なので
    // ここに書き足していっちゃいます．

    let verified = '<svg width="32" height="32" class="octicon octicon-verified" viewBox="0 0 16 16" version="1.1" aria-hidden="true"><circle fill="#2cbe4e" cx="8" cy="8" r="8" /><path fill="white" fill-rule="evenodd" d="M6.5 12.01L3 8.51l1.5-1.5 2 2 5-5L13 5.56l-6.5 6.45z"></path></svg>';

    let unverified = '<svg width="32" height="32" class="octicon octicon-unverified" viewBox="0 0 16 16" version="1.1" aria-hidden="true"><circle fill="#6f42c1" cx="8" cy="8" r="8" /><path fill="white" fill-rule="evenodd" d="M9 11.5c0 .28-.22.5-.5.5h-1c-.27 0-.5-.22-.5-.5v-1c0-.28.23-.5.5-.5h1c.28 0 .5.22.5.5v1zm1.56-4.89c-.06.17-.17.33-.3.47-.13.16-.14.19-.33.38-.16.17-.31.3-.52.45-.11.09-.2.19-.28.27-.08.08-.14.17-.19.27-.05.1-.08.19-.11.3-.03.11-.03.13-.03.25H7.13c0-.22 0-.31.03-.48.03-.19.08-.36.14-.52.06-.14.14-.28.25-.42.11-.13.23-.25.41-.38.27-.19.36-.3.48-.52.12-.22.2-.38.2-.59 0-.27-.06-.45-.2-.58-.13-.13-.31-.19-.58-.19-.09 0-.19.02-.3.05-.11.03-.17.09-.25.16-.08.07-.14.11-.2.2a.41.41 0 00-.09.28h-2c0-.38.13-.56.27-.83.16-.27.36-.5.61-.67.25-.17.55-.3.88-.38.33-.08.7-.13 1.09-.13.44 0 .83.05 1.17.13.34.09.63.22.88.39.23.17.41.38.55.63.13.25.19.55.19.88 0 .22 0 .42-.08.59l-.02-.01z"></path></svg>';

    let failed = '<svg width="32" height="32" class="octicon octicon-x" viewBox="0 0 16 16" version="1.1" aria-hidden="true"><circle fill="#d73a49" cx="8" cy="8" r="8" /><path fill="white" fill-rule="evenodd" d="M9.48 8l3.75 3.75-1.48 1.48L8 9.48l-3.75 3.75-1.48-1.48L6.52 8 2.77 4.25l1.48-1.48L8 6.52l3.75-3.75 1.48 1.48L9.48 8z"></path></svg>';

    let question = '<svg width="32" height="32" class="octicon octicon-q" viewBox="0 0 16 16" version="1.1" aria-hidden="true"><circle fill="#d73a49" cx="8" cy="8" r="8" /><path fill="white" fill-rule="evenodd" d="M9 11.5c0 .28-.22.5-.5.5h-1c-.27 0-.5-.22-.5-.5v-1c0-.28.23-.5.5-.5h1c.28 0 .5.22.5.5v1zm1.56-4.89c-.06.17-.17.33-.3.47-.13.16-.14.19-.33.38-.16.17-.31.3-.52.45-.11.09-.2.19-.28.27-.08.08-.14.17-.19.27-.05.1-.08.19-.11.3-.03.11-.03.13-.03.25H7.13c0-.22 0-.31.03-.48.03-.19.08-.36.14-.52.06-.14.14-.28.25-.42.11-.13.23-.25.41-.38.27-.19.36-.3.48-.52.12-.22.2-.38.2-.59 0-.27-.06-.45-.2-.58-.13-.13-.31-.19-.58-.19-.09 0-.19.02-.3.05-.11.03-.17.09-.25.16-.08.07-.14.11-.2.2a.41.41 0 00-.09.28h-2c0-.38.13-.56.27-.83.16-.27.36-.5.61-.67.25-.17.55-.3.88-.38.33-.08.7-.13 1.09-.13.44 0 .83.05 1.17.13.34.09.63.22.88.39.23.17.41.38.55.63.13.25.19.55.19.88 0 .22 0 .42-.08.59l-.02-.01z"></path></svg>';

    $('img[title=":heavy_check_mark:"]').replaceWith(verified);
    $('img[title=":warning:"]').replaceWith(unverified);
    $('img[title=":x:"]').replaceWith(failed);
    $('img[title=":question:"]').replaceWith(question);

    $('li svg').attr({
        width: 20,
        height: 20,
    }).css({
        'vertical-align': 'text-bottom',
    });

    let numOfPassedTests = $('#verify-files').next().find('li svg.octicon-verified').length;
    let suffix = ((numOfPassedTests != 1)? 's': '');
    $('#verify-files').append(` <small>[passed ${numOfPassedTests} test${suffix}]</small>`);

    {
        let $commitBadge = $('a[href="https://github.com/rsk0315/library"]');
        // https://atcoder-badges.now.sh/
        // $commitBadge.after(' [![rsk0315](https://img.shields.io/endpoint?url=https%3A%2F%2Fatcoder-badges.now.sh%2Fapi%2Fatcoder%2Fjson%2Frsk0315)](https://atcoder.jp/users/rsk0315)');
        // ここでこれを追加してもタグになってくれないじゃん！
        let $ratingBadge = $('<img>').attr({
            alt: 'rsk0315',
            src: 'https://img.shields.io/endpoint?url=https%3A%2F%2Fatcoder-badges.now.sh%2Fapi%2Fatcoder%2Fjson%2Frsk0315'
        });
        let $a = $('<a>').attr({
            href: 'https://atcoder.jp/users/rsk0315',
        });
        $a.html($ratingBadge);
        $commitBadge.after($a);
        $commitBadge.after(' ');
    }
});
