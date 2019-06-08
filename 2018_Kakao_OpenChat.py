'''
    50분 소요, uid를 키로 하고, name을 value로 하는 딕셔너리를 관리
    쓸데없이 닉네임변경 유저배열에 메시지 배열을 돌면서 시간낭비를 하고 있어 시간초과가 떴다
    심플하게 생각하자!
'''

user_dict = dict()
message_list = list()
change_list = dict()
answer = list()

ENTER_MESSAGE = "님이 들어왔습니다."
LEAVE_MESSAGE = "님이 나갔습니다."


record = ["Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan"]

def EnterRoom(uid, name):
    msg = {'uid': uid, 'name': name, 'msg': ENTER_MESSAGE}
    message_list.append(msg)
    if uid in user_dict:
        change_list[uid] = name
    user_dict[uid] = name


def LeaveReoom(uid):
    name = user_dict[uid]
    msg = {'uid': uid, 'name': name, 'msg': LEAVE_MESSAGE}
    message_list.append(msg)


def ChangeName(uid, name):
    user_dict[uid] = name
    change_list[uid] = name

def UpdateMessege():
    for user in change_list:
        for msg in message_list:
            if msg['uid'] == user:
                msg['name'] = user_dict[user]


def solution(record):
    for item in record:
        items = item.split(" ")
        oper = items[0]
        print(" %s ".center(50,"#") %items)
        if oper == "Enter":
            EnterRoom(items[1], items[2])
        elif oper == "Leave":
            LeaveReoom(items[1])
        else:
            ChangeName(items[1], items[2])
    # UpdateMessege()
    for item in message_list:
        print(user_dict[item['uid']] + item['msg'])
        answer.append(user_dict[item['uid']]+item['msg'])

    return answer

solution(record)