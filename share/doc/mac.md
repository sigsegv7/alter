# Mandatory access control

Alter is an operating system that relies on mandatory access control for maintaining
the security of its users, data and state. It can be seen as like an onion with layers,
where the inner-most layer has the highest permissions. Below is a table describing the
security levels that exist:

```
0  :  GUEST     [VIEW-ONLY, LIMITED ACCESS]
1  :  USER      [SELECTED MUTABLE STATE, NORMAL ACCESS]
2  :  OPERATOR  [ELEVATED PERMISSIONS]
```
