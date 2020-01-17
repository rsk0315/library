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
});