要素更新・区間和取得のセグメント木です。

どう書くのがいいんだろうね。
あと名前が気に入っていません。

## テンプレート引数
- `Monoid`
  - default constructor が単位元のモノイドです。
  - `operator +=` と `operator +` が定義されている必要があります。

## public 関数

### コンストラクタ
```c++
basic_segment_tree();
```

空の配列で初期化します。

```c++
explicit basic_segment_tree(size_type n);
```

$a\_0, a\_1, \\dots, a\_n$ を単位元で初期化します。

```c++
basic_segment_tree(size_type n, value_type const& x);
```

$a\_0, a\_1, \\dots, a\_n$ を $x$ で初期化します。

```c++
template <typename InputIt>
basic_segment_tree(InputIt first, InputIt last);
```

$a\_0, a\_1, \\dots, a\_n$ を範囲 $[\\mathit{first}, \\mathit{last})$ の値で初期化します。

## 備考
`utility/monoid/` にあるクラスを使うことで、区間最小値取得などに対応させます。

`std::reverse_iterator` が `operator ++` で元のイテレータの `operator --` を呼び出すのと似ている気がします。
adaptor とか呼ばれていそうです。
