<subhead>Type</subhead>
<header>MapSide</header>

Represents a map sidedef.

### Inherits <type>[MapObject](MapObject.md)</type>  
All properties and functions of <type>[MapObject](MapObject.md)</type> can be used in addition to those below.

## Properties

| Property | Type | Description |
|:---------|:-----|:------------|
<prop class="ro">sector</prop> | <type>[MapSector](MapSector.md)</type> | The side's associated sector
<prop class="ro">line</prop> | <type>[MapLine](MapLine.md)</type> | The side's parent line
<prop class="ro">textureBottom</prop> | <type>string</type> | The side's bottom (lower) texture
<prop class="ro">textureMiddle</prop> | <type>string</type> | The side's middle texture
<prop class="ro">textureTop</prop> | <type>string</type> | The side's top (upper) texture
<prop class="ro">offsetX</prop> | <type>integer</type> | Texture X offset
<prop class="ro">offsetY</prop> | <type>integer</type> | Texture Y offset

## Constructors

!!! attention "No Constructors"
    This type can not be created directly in scripts.

**See:**

* <code>[Map.sidedefs](Map.md#properties)</code>
