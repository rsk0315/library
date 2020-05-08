要素更新・区間和取得のセグメント木です。

どう書くのがいいんだろうね。
あと名前が気に入っていません。

## テンプレート引数
- `Monoid`
  - default constructor が単位元のモノイドです。
  - `operator +=` と `operator +` が定義されている必要があります。

## public 関数

### コンストラクタ
```
basic_segment_tree();
```

空列で初期化します。

```
explicit basic_segment_tree(size_type n);
```

$a\_0, a\_1, \\dots, a\_{n-1}$ を単位元で初期化します。

```
basic_segment_tree(size_type n, value_type const& x);
```

$a\_0, a\_1, \\dots, a\_{n-1}$ を $x$ で初期化します。

```
template <typename InputIt>
basic_segment_tree(InputIt first, InputIt last);
```

$a\_0, a\_1, \\dots, a\_{n-1}$ を範囲 $[\\mathit{first}, \\mathit{last})$ の値で初期化します。
$n$ は範囲の長さです。

### メンバ関数

```
void assign(size_type n, value_type const& x);
template <typename InputIt first, InputIt last>
void assign(first, last);
```

値 $x$ や範囲 $[\\mathit{first}, \\mathit{last})$ の値を代入します。
計算量は $O(n)$ です。

```
void set(size_type i, value_type const& x);
void set(size_type i, value_type&& x);
```

$a\_i$ を $x$ で置き換えます。
計算量は $O(\\log(n))$ です。

```
value_type const& operator [](size_type i) const;
```

$a\_i$ を返します。
計算量は $O(1)$ です。

```
value_type fold(size_type l, size_type r) const;
```

$a\_l + a\_{l+1} + \\dots + a\_{r-1}$ を返します。
計算量は $O(\\log(n))$ です。

```
template <typename Predicate>
size_type foldl_bisect(size_type l, Predicate pred) const;
```

$\\mathtt{fold}(l, n)$ が真の場合は `size_type` の `-1` を返します。
そうでない場合、$\\mathit{pred}(\\mathtt{fold}(l, r))$ が真になるような最大の $r$ を返します。
計算量は $O(\\log(n))$ です。

```
template <typename Predicate>
size_type foldr_bisect(size_type r, Predicate pred) const;
```

$\\mathit{pred}(\\mathtt{fold}(0, r))$ が真の場合は `size_type` の `-1` を返します。
そうでない場合、$\\mathit{pred}(\\mathtt{fold}(l, r))$ が偽になるような最大の $l$ を返します。
計算量は $O(\\log(n))$ です。

`fold*_bisect` で返される境界値について補足します。
返ってきた添字の値を含めて足した場合は述語が偽になり、含めなかった場合は真になります。

`foldl_bisect(l, pred)` の返り値を $r$ とすると、$[l, r)$ の和では真で、$[l, r]$ の和では偽です。
`foldr_bisect(r, pred)` の返り値を $l$ とすると、$(l, r)$ の和では真で、$[l, r)$ の和では偽です。
`foldl_bisect(n, pred)` と呼び出して、単位元で真になる場合は注意がいるかもしれません。

## 備考
`utility/monoid/` にあるクラスを使うことで、区間最小値取得などに対応させます。

`std::reverse_iterator` が `operator ++` で元のイテレータの `operator --` を呼び出すのと似ている気がします。
adaptor とか呼ばれていそうです。
